#include "include/Channel.h"
#include <cstdint>
#include <functional>
#include <sys/epoll.h>
#include <unistd.h>
//#include <utility>
#include "include/EventLoop.h"
//#include "include/Socket.h"

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop),       //事件循环
      fd_(fd),           //文件描述符
      listen_events_(0), //监听中的事件数量
      ready_events_(0),  //已就绪的事件数量
      in_epoll_(false)   //是否在epoll红黑树中
{}

Channel::~Channel() {
  if (fd_ == -1) {
    close(fd_);
    fd_ = -1;
  }
}

void Channel::HandleEvent() {
  if (ready_events_ & (EPOLLIN | EPOLLPRI)) {
    read_callback_(); //调用读取回调函数
  }
  if (ready_events_ & (EPOLLOUT)) {
    write_callback_(); //调用写入回调函数
  }
}

void Channel::EnableRead() {
  listen_events_ |= EPOLLIN | EPOLLPRI;
  loop_->UpdateChannel(this); //更新当前Channel对象
}
// Epoll使用边缘触发模式
void Channel::UseET() {
  listen_events_ |= EPOLLET;
  loop_->UpdateChannel(this);
}

int Channel::GetFd() { return fd_; }

uint32_t Channel::GetListenEvents() { return listen_events_; }

uint32_t Channel::GetReadyEvents() { return ready_events_; }

bool Channel::GetInEpoll() { return in_epoll_; }

void Channel::SetInEpoll(bool in) { in_epoll_ = in; }

void Channel::SetReadyEvents(uint32_t ev) { ready_events_ = ev; }
void Channel::SetReadCallback(std::function<void()> const &callback) {
  read_callback_ = callback;
}