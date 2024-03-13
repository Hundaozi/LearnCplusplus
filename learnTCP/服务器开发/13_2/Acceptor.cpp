#include "include/Acceptor.h"
#include "include/Channel.h"
#include "include/Socket.h"
#include <functional>
#include <stdio.h>
#include <utility>
Acceptor::Acceptor(EventLoop *loop)
    : loop_(loop), sock_(nullptr), channel_(nullptr) {
  sock_ = new Socket();
  InetAddress *addr = new InetAddress("127.0.0.1", 4490);
  sock_->Bind(addr);
  // sock_->SetNonBlocking();接收器使用阻塞式io
  sock_->Listen();
  channel_ = new Channel(loop_, sock_->GetFd());
  std::function<void()> cb = std::bind(&Acceptor::AcceptConnection, this);
  channel_->SetReadCallback(cb);
  channel_->EnableRead();
  delete addr;
}

Acceptor::~Acceptor() {
  delete channel_;
  delete sock_;
}

void Acceptor::AcceptConnection() {
  InetAddress *client_addr = new InetAddress(); //实例一个客户端地址
  //
  Socket *client_sock = new Socket(sock_->Accept(client_addr));
  printf("new client fd %d! IP: %s Port: %d\n", client_sock->GetFd(),
         client_addr->GetIp(), client_addr->GetPort());
  //将客户端的socket设置为非阻塞模式
  client_sock->SetNonBlocking();
  new_connection_callback_(client_sock);
  delete client_addr; //没用了
}

void Acceptor::SetNewConnectionCallback(
    std::function<void(Socket *)> const &callback) {
  new_connection_callback_ = callback;
}