#include "Socket.h"
#include "InetAddress.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>

Socket::Socket(): socket_fd (-1){
    //使用数据流传递，使用默认协议（TCP）
    socket_fd= socket(AF_INET, SOCK_STREAM, 0);
    
}

Socket::Socket(){}

Socket::~Socket(){}

void Socket::bind(InetAddress* _addr){}

void Socket::listen(){}

void Socket::setnonblocking(){}

int Socket::accept(InetAddress* _addr){}

int Socket::get_socket_fd(){
    return socket_fd;
}
