#pragma once
#include "Macros.h"
#include <functional>

class Epoll;
class Channel;
//事件循环类
class EventLoop {
public:
  EventLoop();
  ~EventLoop();

  DISALLOW_COPY_AND_MOVE(EventLoop);
  //循环
  void Loop();
  //更新管道
  void UpdateChannel(Channel *ch);

private:
  Epoll *epoll_{nullptr};
  bool quit_{false};
};