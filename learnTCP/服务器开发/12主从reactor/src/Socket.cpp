#include "Socket.h"
#include "util.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
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

void Socket::bind(InetAddress *_addr){
    struct sockaddr_in addr = _addr->getAddr();
    error(::bind(socket_fd, (sockaddr*)&addr, sizeof(addr)) == -1, "socket bind error");
}


void Socket::listen(){
    error(::listen(socket_fd, SOMAXCONN) == -1, "socket listen error");
}
//设置为非阻塞模式
void Socket::setnonblocking(){
    fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress *_addr){
    // for server socket
    int clnt_sockfd = -1;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    socklen_t addr_len = sizeof(addr);
    if(fcntl(socket_fd, F_GETFL) & O_NONBLOCK){
        while(true){
            clnt_sockfd = ::accept(socket_fd, (sockaddr*)&addr, &addr_len);
            if(clnt_sockfd == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
                // printf("no connection yet\n");
                continue;
            } else if(clnt_sockfd == -1){
                error(true, "socket accept error");
            } else{
                break;
            }
        }
    }
    else{
        clnt_sockfd = ::accept(socket_fd, (sockaddr*)&addr, &addr_len);
        error(clnt_sockfd == -1, "socket accept error");
    }
    _addr->setInetAddr(addr);
    return clnt_sockfd;
}

int Socket::get_socket_fd(){
    return socket_fd;
}



void Socket::connect(InetAddress *_addr){
    // for client socket
    struct sockaddr_in addr = _addr->getAddr();
    if(fcntl(socket_fd, F_GETFL) & O_NONBLOCK){
        while(true){
            int ret = ::connect(socket_fd, (sockaddr*)&addr, sizeof(addr));
            if(ret == 0){
                break;
            } else if(ret == -1 && (errno == EINPROGRESS)){
                continue;
            /* 连接非阻塞式sockfd建议的做法：
                The socket is nonblocking and the connection cannot be
              completed immediately.  (UNIX domain sockets failed with
              EAGAIN instead.)  It is possible to select(2) or poll(2)
              for completion by selecting the socket for writing.  After
              select(2) indicates writability, use getsockopt(2) to read
              the SO_ERROR option at level SOL_SOCKET to determine
              whether connect() completed successfully (SO_ERROR is
              zero) or unsuccessfully (SO_ERROR is one of the usual
              error codes listed here, explaining the reason for the
              failure).
              这里为了简单、不断连接直到连接完成，相当于阻塞式
            */
            } else if(ret == -1){
                error(true, "socket connect error");
            }
        }
    } else{
        error(::connect(socket_fd, (sockaddr*)&addr, sizeof(addr)) == -1, "socket connect error");
    }
}

InetAddress::InetAddress(){
    bzero(&addr,sizeof(addr));
}

InetAddress::InetAddress(const char* _ip, uint16_t _port) {
    bzero(&addr,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(_ip);
    addr.sin_port=htons(_port);
}
InetAddress::~InetAddress(){
}

void InetAddress::setInetAddr(sockaddr_in _addr){
    addr=_addr;
}
sockaddr_in InetAddress::getAddr(){
    return addr;
}
char* InetAddress::getIp(){
    return inet_ntoa(addr.sin_addr);
}
uint16_t InetAddress::getPort(){
    return ntohs(addr.sin_port);
}