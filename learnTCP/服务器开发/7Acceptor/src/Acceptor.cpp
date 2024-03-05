#include "Acceptor.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "Server.h"

Acceptor::Acceptor(EventLoop * _loop): loop(_loop){
    sock =new Socket();
    addr=new InetAddress("127.0.0.1",4490);
    sock->bind(addr);
    sock->listen();
    acceptChannel = new Channel(loop,sock->getFd());
    std::function<void()> cb=std::bind(&Acceptor::acceptConnection,this);
    acceptChannel->setCallback(cb);
    acceptChannel->enableReading();
}

Acceptor::~Acceptor(){
    delete sock;
    delete addr;
    delete acceptChannel;
    //现在不会泄露了
}

void Acceptor::acceptConnection(){
    //连接接受一个socket
    newConnectionCallback(sock);
}

void Acceptor::set_newConnectionCallback(std::function<void(Socket*)> _cb){
    newConnectionCallback=_cb;

}