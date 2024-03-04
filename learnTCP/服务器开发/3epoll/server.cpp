#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>   //此库是什么，不太清楚，先导入再说
#include <sys/epoll.h> //epoll的库，害得我买了一台云主机
#include <errno.h> //异常处理
#include "util.h"


#define MAX_EVENTS 1024
#define READ_BUFFER 1024

//非阻塞
//#ifndef __USE_FILE_OFFSET64
//extern int fcntl (int __fd, int __cmd, ...);
//#else
void setnonblocking(int fd){
    /* Values for the second argument to `fcntl'.  */
    //#define F_DUPFD		0	/* Duplicate file descriptor.  */
    //#define F_GETFD		1	/* Get file descriptor flags.  */
    //#define F_SETFD		2	/* Set file descriptor flags.  */
    //#define F_GETFL		3	/* Get file status flags.  */
    //#define F_SETFL		4	/* Set file status flags.  */
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int main(){
    //原来最后一位是协议的意思，默认为0
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    errif(sockfd==-1,"socket 创建错误");

    struct sockaddr_in server_addr;
    //void	 bzero(void *, size_t) __POSIX_C_DEPRECATED(200112L);
    //传一个指针，然后是大小，后面的参数，有点不懂。。。200112L?
    //#define __POSIX_C_DEPRECATED(ver) ___POSIX_C_DEPRECATED_STARTING_##ver
    bzero(&server_addr,sizeof(server_addr));

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    //#define htons(x)        __DARWIN_OSSwapInt16(x)
    server_addr.sin_port=htons(4490);

    errif(bind(sockfd,(sockaddr*)&server_addr,sizeof(server_addr))==-1,"socket bind错误");

    //原来如此，侦听可指定的最大队列长度。
    errif(listen(sockfd,SOMAXCONN)==-1,"socket listen 错误");
    //
    /*
    * Maximum queue length specifiable by listen.
    */
    //#define SOMAXCONN       128

    //extern int epoll_create1 (int __flags) __THROW;
    int epfd=epoll_create1(0);//默认
    errif(epfd==-1,"epoll 创建错误");
    struct epoll_event events[MAX_EVENTS], ev;
    //实际上就是两个结构体
    bzero(&events,sizeof(events));//初始化缓冲区
    bzero(&ev, sizeof(ev));

    ev.data.fd = sockfd;
    ev.events = EPOLLIN | EPOLLET;//哦哦，其实里面是一个enum
    //struct epoll_event
    //{
    //uint32_t events;	/* Epoll events */
    //epoll_data_t data;	/* User data variable */
    //} __EPOLL_PACKED; 

    setnonblocking(sockfd);
    //文件，操作,就是填一个文件描述符给接口，还有sockfd，以及ev的地址
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
    ///* Valid opcodes ( "op" parameter ) to issue to epoll_ctl().  */
    //#define EPOLL_CTL_ADD 1	/* Add a file descriptor to the interface.  */
    //#define EPOLL_CTL_DEL 2	/* Remove a file descriptor from the interface.  */
    //#define EPOLL_CTL_MOD 3	/* Change file descriptor epoll_event structure.  */

    while (true)

    {
        /* code */
        int nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
        errif(nfds==-1,"epoll wait 错误");

        for(int i=0;i<nfds;++i){
            //从0开始一个个处理
            if(events[i].data.fd==sockfd)
            {
                //如果sockfd等于事件中存储的fd
                struct sockaddr_in client_addr;//声明客户端的地址
                bzero(&client_addr,sizeof(client_addr));//清空缓冲区
                socklen_t client_addr_length=sizeof(client_addr);//获取客户端地址的长度

                int client_sockfd=accept(sockfd,(sockaddr*)&client_addr,&client_addr_length);
                //接受fd
                errif(client_sockfd==-1,"socket accept 错误");
                printf("new client fd %d! IP: %s Port: %d\n", client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                bzero(&ev,sizeof(ev));
                ev.data.fd=client_sockfd;
                ev.events=EPOLLIN | EPOLLET;//IN是水平触发，ET是边缘触发
                setnonblocking(client_sockfd);
                //作用： 向文件描述符epfd引用的epoll实例执行控制操作
                //EPOLL_CTL_ADD	在epoll的监视列表中添加一个文件描述符(即参数fd)，指定监视的事件类型(参数event)
                //EPOLL_CTL_MOD	修改监视列表中已经存在的描述符(即参数fd)对应的监视事件类型(参数event)
                //EPOLL_CTL_DEL	将某监视列表中已经存在的描述符(即参数fd)删除，参数event传NULL
                epoll_ctl(epfd, EPOLL_CTL_ADD,client_sockfd,&ev);

            }else if (events[i].events & EPOLLIN)//可读事件
            {
                char buffer[READ_BUFFER];
                //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
                while (true)
                {

                    //将事件中的数据读取到缓冲区
                    ssize_t bytes_read=read(events[i].data.fd,buffer,sizeof(buffer));
                    //如果有数据
                    if(bytes_read>0){
                        printf("message from client fd %d: %s\n", events[i].data.fd, buffer);
                        //将客户端的数据写入缓冲区
                        write(events[i].data.fd,buffer,sizeof(buffer));
                    
                    }else if (bytes_read==-1 &&errno==EINTR)
                    {
                        //#define	EINTR		 4	/* Interrupted system call */
                        ////客户端正常中断、继续读取
                        /* code */
                        printf("继续读取......");
                        continue;
                    }else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
                    {   
                        //非阻塞IO，这个条件表示数据全部读取完毕
                        printf("完成读取一次，errno: %d\n",errno );
                        break;//跳出

                    }else if (bytes_read==0)
                    {
                        //客户端断开连接
                        printf("EOF, 客户端 fd： %d 断开连接.\n",events[i].data.fd);
                        close(events[i].data.fd);//关闭socket会自动将文件描述符从epoll树上移除
                        //epoll树是红黑树，大量读取插入平均性能最好
                        break;
                    }
                }
                        
            }else{
                printf("其他未知情况.\n");
            }
        }
    }
    close(sockfd);
    return 0;
}