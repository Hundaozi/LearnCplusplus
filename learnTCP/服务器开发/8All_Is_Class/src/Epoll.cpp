#include "Epoll.h"
#include "util.h"
#include "Channel.h"
#include <unistd.h>
#include <string.h>

#define MAX_EVENTS 1000

Epoll::Epoll() : epoll_fd(-1), epoll_events(nullptr){
    epoll_fd = epoll_create1(0);
    error(epoll_fd == -1, "epoll 创建错误！\n");
    epoll_events = new epoll_event[MAX_EVENTS];
    bzero(epoll_events, sizeof(*epoll_events) * MAX_EVENTS);
}

Epoll::~Epoll(){
    if(epoll_fd != -1){
        close(epoll_fd);
        epoll_fd = -1;
    }
    delete [] epoll_events;
}

std::vector<Channel*> Epoll::poll(int _timeout){
    //用一个向量存储活跃的Channel
    std::vector<Channel*> activeChannels;
    //等待监听的所有fd相应事件的产生
    auto nfds = epoll_wait(epoll_fd, epoll_events, MAX_EVENTS, _timeout);
    error(nfds == -1, "epoll wait 错误！\n");
    for(auto i = 0; i < nfds; ++i){
        Channel *ch = (Channel*)epoll_events[i].data.ptr;
        ch->setRevents(epoll_events[i].events);
        activeChannels.push_back(ch);
    }
    return activeChannels;
}

void Epoll::updateChannel(Channel *_channel){
    int fd = _channel->getFd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = _channel;
    ev.events = _channel->getEvents();
    if(!_channel->getInEpoll()){
        error(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add 错误！\n");
        _channel->setInEpoll();   
    } else{
        error(epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll modify 错误！\n");
    }
}