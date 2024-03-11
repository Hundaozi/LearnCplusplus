#include "include/Server.h"
#include "include/Acceptor.h"
#include "include/Connection.h"
#include "include/EventLoop.h"
#include "include/Socket.h"
#include "include/ThreadPool.h"
#include "include/util.h"
#include <cstdint>
#include <functional>
#include <unistd.h>

Server::Server(EventLoop *loop)
    : main_reactor_(loop), acceptor_(nullptr), thread_pool_(nullptr) {
  acceptor_ = new Acceptor(main_reactor_);
  //_1用于代替回调函数中的第一个参数,实际上就是一个占位符
  std::function<void(Socket *)> cb =
      std::bind(&Server::NewConnection, this, std::placeholders::_1);
  auto thread_size_ = static_cast<int>(std::thread::hardware_concurrency());
  thread_pool_ = new ThreadPool(thread_size_);
  for (auto i = 0; i < thread_size_; ++i) {
    //主reac只负责管理
    //将任务函数push到从Reactor中
    sub_reactors_.push_back(new EventLoop());
  }
  for (auto i = 0; i < thread_size_; ++i) {
    std::function<void()> sub_loop =
        std::bind(&EventLoop::Loop, sub_reactors_[i]);
    thread_pool_->Add(std::move(sub_loop)); //将任务函数都添加进线程池中
  }
}

Server::~Server() {
  delete acceptor_;
  delete thread_pool_;
}

void Server::NewConnection(Socket *sock) {
  ErrorIf(sock->GetFd() == -1, "new connection error");
  uint64_t random = sock->GetFd() % sub_reactors_.size();
  Connection *conn = new Connection(sub_reactors_[random], sock);
  std::function<void(int)> cb =
      std::bind(&Server::DeleteConnection, this, std::placeholders::_1);
  conn->SetDeleteConnectionCallback(cb);
  connections_[sock->GetFd()] = conn;
}

void Server::DeleteConnection(int sockfd) {
  auto it = connections_.find(sockfd); //先找到它的文件描述符
  if (it != connections_.end()) {
    Connection *conn = connections_[sockfd];
    connections_.erase(sockfd);
    delete conn;
  }
}