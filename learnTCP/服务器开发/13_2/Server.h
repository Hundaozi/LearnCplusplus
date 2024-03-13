#pragma once
#include "Macros.h"
#include <map>
#include <vector>
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class ThreadPool;
class Server {

private:
  EventLoop *main_reactor_;
  Acceptor *acceptor_;
  std::map<int, Connection *> connections_;
  std::vector<EventLoop *> sub_reactors_;
  ThreadPool *thread_pool_;

public:
  explicit Server(EventLoop *loop);
  ~Server();

  //DISALLOW_COPY_AND_MOVE(Server);
  //建立新的TCP连接
  void NewConnection(Socket *sock);
  //删除TCP连接
  void DeleteConnection(int sockfd);
};