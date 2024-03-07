#include "Server.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
#include <unistd.h>
#include <functional>

Server::Server(EventLoop *_loop) : loop(_loop), acceptor(nullptr){ 
    acceptor = new Acceptor(loop);
    //std::placeholders::_1：表示第一个未指定的参数。
    //std::placeholders::_2：表示第二个未指定的参数。
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);
}

Server::~Server(){
    delete acceptor;
}


void Server::newConnection(Socket *_sock){
    if(_sock->get_socket_fd() != -1){
        Connection *conn =new Connection(loop,_sock);
        std::function<void(int)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
        conn->setDeleteConnectionCallback(cb);
        connections[_sock->get_socket_fd()]=conn;
    }

}

void Server::deleteConnection(int _sockfd){
    if(_sockfd != -1){    
        if(auto it=connections.find(_sockfd);it != connections.end()){
            Connection *conn=connections[_sockfd];
            connections.erase(_sockfd);
            close(_sockfd);
            delete conn;
        }
    }
}