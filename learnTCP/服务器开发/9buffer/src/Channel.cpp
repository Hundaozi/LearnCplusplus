#include "Channel.h"
#include "EventLoop.h"
#include <unistd.h>

Channel::Channel(EventLoop *_event_loop, int _fd) : event_loop(_event_loop), fd(_fd), events(0), revents(0), inEpoll(false){

}

Channel::~Channel(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Channel::handleEvent(){
    callback();
}

void Channel::enableReading(){
    //EPOLLIN水平触发，一直询问
    //EPOLLET边缘出发，只问一次
    events |= EPOLLIN | EPOLLET;
    event_loop->updateChannel(this);
}

int Channel::getFd(){
    return fd;
}

uint32_t Channel::getEvents(){
    return events;
}
uint32_t Channel::getRevents(){
    return revents;
}

bool Channel::getInEpoll(){
    return inEpoll;
}
void Channel::setInEpoll(){
    inEpoll = true;
}
void Channel::setRevents(uint32_t _ev){
    revents = _ev;
}
void Channel::setCallback(std::function<void()> _cb){
    callback = _cb;
}