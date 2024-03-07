#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include <unistd.h>
#include <string.h>
#define READ_BUFFER 1024

Connection::Connection(EventLoop *_loop, Socket *_sock) : loop(_loop), sock(_sock), channel(nullptr){
    channel = new Channel(loop, sock->get_socket_fd());
    //将两个地址，一个fd绑定在一起
    std::function<void()> cb = std::bind(&Connection::echo , this , sock->get_socket_fd());
    channel->setCallback(cb);
    channel->enableReading();//设置监听状态
}
//断开连接
Connection::~Connection(){
    delete channel;
    delete sock;
}

void Connection::echo(int _sockfd){
    char buffer[READ_BUFFER];
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buffer, sizeof(buffer));
        ssize_t read_bytes = read(_sockfd, buffer, sizeof(buffer));
        if(read_bytes > 0){
            printf("从客户端:fd %d接受消息 : %s\n", _sockfd, buffer);
            write(_sockfd, buffer, sizeof(buffer));
        } else if(read_bytes == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("正在读取中......");
            continue;
        } else if(read_bytes == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("成功接受消息一次, err码: %d\n", errno);
            break;
        } else if(read_bytes == 0){  //EOF，客户端断开连接
            printf("客户端 fd %d 已断开连接。\n", _sockfd);
            // close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            deleteConnectionCallback(sock);
            break;
        }
    }
}

void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> _cb){
    deleteConnectionCallback = _cb;
}