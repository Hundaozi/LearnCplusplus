#include "Server.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include <functional>
#include <string.h>
#include <unistd.h>

#define READ_BUFFER 1024

Server::Server(EventLoop *_loop):loop(_loop){
    Socket * server_sock=new Socket();
    InetAddress *server_addr=new InetAddress("127.0.0.1",4490);
    server_sock->bind(server_addr);
    server_sock->listen();
    server_sock->setnonblocking();
    //功能描述：根据文件描述词来操作文件的特性。 
    
    // 用法：   
    // int fcntl(int fd, int cmd); 
    // int fcntl(int fd, int cmd, long arg); 
    // int fcntl(int fd, int cmd, struct flock *lock); 
    //最后的参数O_NONBLOCK表明使用非阻塞模式

    Channel *serverChannel=new Channel(loop,server_sock->get_fd());
    //socket套娃，底层还是linux的sock库
    //作用于一个server实例
    std::function<void()> cb=std::bind(&Server::newConnection, this, server_sock);
    serverChannel->setCallback(cb);
    serverChannel->enableReading();

}

Server::~Server()
{
    
}

void Server::handleReadEvent(int sockfd){
    char buffer[READ_BUFFER];
    //非阻塞io
    while (true)
    {
        /* code */
        bzero(&buffer,sizeof(buffer));
        ssize_t read_bytes=read(sockfd,buffer,sizeof(buffer));
        if(read_bytes>0){
            printf("message from client fd %d: %s\n", sockfd, buffer);
            write(sockfd, buffer, sizeof(buffer));
        }else if(read_bytes == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else if(read_bytes == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if(read_bytes == 0){  //EOF，客户端断开连接
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }      
    }
}

void Server::newConnection(Socket *server_sock){
    InetAddress* client_addr=new InetAddress();
    Socket *client_sock=new Socket(server_sock->accept(client_addr));
    printf("new client fd %d! IP: %s Port: %d\n", 
        client_sock->get_fd(),
        inet_ntoa(client_addr->addr.sin_addr), 
        ntohs(client_addr->addr.sin_port));
    client_sock->setnonblocking();//设置为非阻塞
    //这里还会有内存泄露，因为没有delete

    Channel *clientChannel= new Channel(loop,client_sock->get_fd());
    std::function<void()> cb=std::bind(&Server::handleReadEvent, this, client_sock->get_fd());
    clientChannel->setCallback(cb);
    clientChannel->enableReading();

}