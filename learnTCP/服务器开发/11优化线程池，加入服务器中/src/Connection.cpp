#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include "Buffer.h"
#include <unistd.h>
#include <string.h>
#define READ_BUFFER 1024

Connection::Connection(EventLoop *_loop, Socket *_sock) : 
    loop(_loop), sock(_sock), 
    channel(nullptr)
    {
        channel = new Channel(loop, sock->get_socket_fd());
        channel->enableReading();
        channel->useET();
        //将两个地址，一个fd绑定在一起
        std::function<void()> cb = std::bind(&Connection::echo , this , sock->get_socket_fd());
        channel->set_Read_Callback(cb);
        channel->set_Use_ThreadPool(true);
        readBuffer=new Buffer();
}
//断开连接
Connection::~Connection(){
    delete channel;
    delete sock;
    delete readBuffer;
}

void Connection::echo(int _sockfd){
    char buffer[READ_BUFFER];
    while(true){    //由于使用非阻塞IO，读取客户端buffer，一次读取buf大小数据，直到全部读取完毕
        bzero(&buffer, sizeof(buffer));
        ssize_t read_bytes = read(_sockfd, buffer, sizeof(buffer));
        if(read_bytes > 0){
            readBuffer->append(buffer,read_bytes);
        } else if(read_bytes == -1 && errno == EINTR){  //客户端正常中断、继续读取
            printf("正在读取中......");
            continue;
        } else if(read_bytes == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//非阻塞IO，这个条件表示数据全部读取完毕
            printf("成功接收客户端fd: %d 的消息: %s \n", _sockfd,readBuffer->c_str());
            send(_sockfd);
            readBuffer->clear();
            break;
        } else if(read_bytes == 0){  //EOF，客户端断开连接
            printf("客户端 fd %d 已断开连接。\n", _sockfd);
            // close(sockfd);   //关闭socket会自动将文件描述符从epoll树上移除
            deleteConnectionCallback(_sockfd);
            break;
        }else{
            printf("Connection reset by peer\n");
            //deleteConnectionCallback(_sockfd);          //会有bug，注释后单线程无bug
            break;
        }
    }
}

void Connection::setDeleteConnectionCallback(std::function<void(int)> _cb){
    deleteConnectionCallback = _cb;
}

void Connection::send(int _sockfd){
    char buf[readBuffer->size()];
    strcpy(buf,readBuffer->c_str());//将要发送的数据拷贝到缓冲区
    int data_size=readBuffer->size();//读取的数据大小
    int data_left_size=data_size; //离开的数据大小
    while(data_left_size > 0)
        {
            ssize_t write_bytes=write(_sockfd,
                buf + data_size - data_left_size,
                data_left_size);
            if(write_bytes== - 1 && errno == EAGAIN){
                break;
            }
            data_left_size = write_bytes;
        }
}