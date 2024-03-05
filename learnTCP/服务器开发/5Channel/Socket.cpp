#include "Socket.h"
#include "InetAddress.h"
#include "util.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

Socket::Socket():fd(-1) {
    //默认协议
    fd=socket(AF_INET,SOCK_STREAM,0);
    errif(fd == -1, "socket create error");

}

//出现了，形参使用下划线
Socket::Socket(int _fd): fd(_fd){
    errif(fd == -1, "socket create error");
}

Socket::~Socket(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Socket::bind(InetAddress *addr){
    //学到了。。
    errif(::bind(fd,(sockaddr*)&addr->addr,addr->addr_len) == -1,"socket bind error ");

}

void Socket::listen(){
    //SOMAXCONN最大监听数：4096
    errif(::listen(fd,SOMAXCONN)==-1,"socket listen error");
}

void Socket::setnonblocking(){
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress *addr){
    int client_sockfd=::accept(fd,(sockaddr*)&addr->addr,&addr->addr_len);
    errif(client_sockfd==-1,"socket accept error");
    return client_sockfd;
}

int Socket::get_fd(){
    return fd;
}