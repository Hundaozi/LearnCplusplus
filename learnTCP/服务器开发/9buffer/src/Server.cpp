#include "Server.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
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
    Connection *conn =new Connection(loop,_sock);
    std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    conn->setDeleteConnectionCallback(cb);
    connections[_sock->get_socket_fd()]=conn;

}

void Server::deleteConnection(Socket * _sock){
    Connection *conn = connections[_sock->get_socket_fd()];
    connections.erase(_sock->get_socket_fd());
    delete conn;
}