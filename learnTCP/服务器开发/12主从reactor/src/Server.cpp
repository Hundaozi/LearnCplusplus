#include "Server.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
#include "threadpool.h"
#include "EventLoop.h"
#include <unistd.h>
#include <functional>
Server::Server(EventLoop *_loop) : main_Reactor(_loop), acceptor(nullptr){ 
    acceptor = new Acceptor(main_Reactor);
    //std::placeholders::_1：表示第一个未指定的参数。
    //std::placeholders::_2：表示第二个未指定的参数。
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);
    // Returns a value that hints at the number of hardware thread contexts.
    auto size= std::thread::hardware_concurrency();

    threadpool= new ThreadPool(size);
    for(auto i=0;i<size;++i){
        sub_Reactors.push_back(new EventLoop());
    }

    for(auto i=0;i<size;++i){
        std::function<void()> sub_loop=std::bind(&EventLoop::loop,sub_Reactors[i]);
        threadpool->add(sub_loop);
    }
}

Server::~Server(){
    delete acceptor;
    delete threadpool;
}


void Server::newConnection(Socket *_sock){
    if(_sock->get_socket_fd() != -1){
        int random=_sock->get_socket_fd()&sub_Reactors.size();
        Connection *conn =new Connection(sub_Reactors[random],_sock);
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
            //close(_sockfd);
            delete conn;
        }
    }
}