#include "include/Epoll.h"
#include "include/Channel.h"
#include "include/util.h"
#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>

//尽量不要使用宏定义，将预处理的东西放在编译期更为严谨
//#define MAX_EVENTS 1000
enum class Max_event :int {
    MAX_EVENTS = 1000
};


Epoll::Epoll(){
    epfd_=epoll_create1(0);
    ErrorIf(epfd_==-1, "epoll create error!");
    auto max=static_cast<int>(Max_event::MAX_EVENTS);
    events_=new epoll_event[max];
    memset(events_, 0, sizeof(*events_) * max);
}

Epoll::~Epoll() {
  if (epfd_ != -1) {
    close(epfd_);
    epfd_ = -1;
  }
  delete[] events_;
}

std::vector<Channel *>Epoll::Poll(int timeout){
  std::vector<Channel *> active_channels;//vector装着指针
  auto max=static_cast<int>(Max_event::MAX_EVENTS);
  int nfds=epoll_wait(epfd_,  events_, max,timeout);
  ErrorIf(nfds == -1, "epoll wait error");
  for(auto i=0;i<nfds;++i){
    Channel *ch=(Channel*)events_[i].data.ptr;
    ch->SetReadyEvents(events_[i].events);
    active_channels.push_back(ch);
  }
  return active_channels;
}

void Epoll::UpdateChannel(Channel *ch){
  auto fd=ch->GetFd();
  struct epoll_event ev{};
  ev.data.ptr=ch;
  ev.events=ch->GetListenEvents();
  if(!ch->GetInEpoll()){
    ErrorIf(epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add error");
    ch->SetInEpoll();
  }else {
    ErrorIf(epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll modify error");
  }
}

void Epoll::DeleteChannel(Channel *ch) {
  auto fd = ch->GetFd();
  ErrorIf(epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, nullptr) == -1, "epoll delete error");
  ch->SetInEpoll(false);
}