#include "Socket.h"
#include "InetAddress.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>
#include "util.h"
Socket::Socket(): socket_fd (-1){
    //使用数据流传递，使用默认协议（TCP）
    socket_fd= socket(AF_INET, SOCK_STREAM, 0);
    error(socket_fd == -1,"Socket 创建错误！\n ");
}

Socket::Socket(int _socket_fd):socket_fd(_socket_fd){
    error(socket_fd == -1, "Socket 创建错误！ \n");
}

Socket::~Socket(){
    if(socket_fd != -1){
        close(socket_fd);
        socket_fd = -1;
    }
}

void Socket::bind(InetAddress* _addr){
    struct sockaddr_in socket_addr=_addr->getAddr();
    socklen_t socket_addr_len=_addr->getAddr_len();
    error(::bind(socket_fd, (sockaddr*)&socket_addr, socket_addr_len) ==-1,"Socket bind 错误！ \n");
    _addr->setInetAddr(socket_addr,socket_addr_len);
}

void Socket::listen(){
    error(::listen(socket_fd,SOMAXCONN) ==-1 ,"Socket listen 错误！ \n");
}
void Socket::setnonblocking(){
    //fcntl是对fd的操作，这里设置为非阻塞模式
    fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress* _addr){
    struct sockaddr_in socket_addr;
    socklen_t socket_addr_len=sizeof(socket_addr);
    bzero(&socket_addr, sizeof(socket_addr));
    int client_socket_fd = ::accept(socket_fd, (sockaddr*)&socket_addr, &socket_addr_len);
    error(client_socket_fd == -1, "Socket accept 错误！ \n");
    _addr->setInetAddr(socket_addr, socket_addr_len);
    return client_socket_fd;

}

int Socket::get_socket_fd(){
    return socket_fd;
}


void Socket::connect(InetAddress* _addr){
    struct sockaddr_in addr=_addr->getAddr();
    socklen_t addr_len=_addr->getAddr_len();
    error(::connect(socket_fd,(sockaddr*)&addr, addr_len)==-1,"socket connect 错误！\n");
}