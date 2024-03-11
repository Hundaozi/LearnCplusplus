#pragma once
#include "Macros.h"
#include <vector>
#ifdef OS_LINUX
#include <sys/epoll.h>
#endif

class Channel;

class Epoll {
public:
  Epoll();
  ~Epoll();

  DISALLOW_COPY_AND_MOVE(Epoll);

  //更新管道
  void UpdateChannel(Channel *ch);
  //删除管道
  void DeleteChannel(Channel *ch);
  //存储着管道类的向量
  std::vector<Channel *> Poll(int timeout = -1);

private:
  int epfd_{1};
  // epoll事件结构体
  struct epoll_event *events_{nullptr};
};