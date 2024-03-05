#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <vector>
#include "util.h"
#include "Epoll.h"
#include "InetAddress.h"
#include "Socket.h"
#include <memory>
#define MAX_EVENTS 1024
#define READ_BUFFER 1024

//非阻塞
void setnonblocking(int fd){
    fcntl(fd, F_SETFL,fcntl(fd,F_GETFL)| O_NONBLOCK);
}

//处理读取事件
//声明缓冲区
//第一步，初始化缓冲区
//第二步，从socket读取数据
//第三步，处理
void handleReadEvent(int sockfd){
    char buffer[READ_BUFFER];
    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
    while(true){
        bzero(&buffer,sizeof(buffer));
        ssize_t read_bytes= read(sockfd,buffer,sizeof(buffer));

        if(read_bytes>0){
            //读取成功，从客户端接收到信息
            printf("message from client fd %d: %s\n", sockfd, buffer);
            write(sockfd, buffer, sizeof(buffer));
        }else if (read_bytes==-1 && errno == EINTR)//客户端正常终端，继续读取，哦，不是错了,昨天没搞明白
        {
            /* code */
            printf("continue reading");
            continue;
        }else if (read_bytes==-1 && ((errno==EAGAIN)||(errno== EWOULDBLOCK))){
            //非阻塞IO，这个条件表示数据全部读取完毕
            //#define	EAGAIN		11	/* Try again */
            //#define	EWOULDBLOCK	EAGAIN	/* Operation would block */
            //两个操作实际上是一个操作？
            printf("finish reading once, errno: %d\n", errno);
            break;

        }else if (read_bytes==0)
        {
            /* code */
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
            //知识点，epoll使用了红黑树
        }
    }
}
//上面的代码还可以再封装，然后使用现代化的语法优化
        
int main(){

    //原始的初始化，应该使用智能指针
    Socket *server_sock=new Socket();
    InetAddress *server_addr=new InetAddress("127.0.0.1",4490);

    //绑定地址
    
    server_sock->bind(server_addr);
    //监听
    server_sock->listen();

    Epoll *ep = new Epoll();
    server_sock->setnonblocking();//这vscode上的提示就是垃圾
    //将socket的fd传给ep，两种触发模式都有
    ep->add_fd(server_sock->get_fd(), EPOLLIN | EPOLLET);

    while(true){
        //获取事件
        std::vector<epoll_event> events=ep->poll();
        //获取事件数量
        auto nfds=events.size();
        for(auto i=0;i<nfds;++i){
            if(events[i].data.fd==server_sock->get_fd()){
                //如果epoll事件中的fd和socket中的fd匹配
                InetAddress *client_addr=new InetAddress(); //会发生内存泄露！没有delete
                Socket *client_sock=new Socket(server_sock->accept(client_addr)); //也会泄露，没有delete
                printf("new client fd %d! IP: %s Port: %d\n", 
                    client_sock->get_fd(), 
                    inet_ntoa(client_addr->addr.sin_addr), 
                    ntohs(client_addr->addr.sin_port));
                client_sock->setnonblocking();
                ep->add_fd(client_sock->get_fd(), EPOLLIN | EPOLLET);
            }else if (events[i].events & EPOLLIN)//水平触发，一直读取
            {
                handleReadEvent(events[i].data.fd);
            }else{
                //其他情况，不会写
                printf("something else happened\n");
            }
            
        }
    }
    //手动释放内存
    delete server_sock;
    delete server_addr;
    return 0;
}