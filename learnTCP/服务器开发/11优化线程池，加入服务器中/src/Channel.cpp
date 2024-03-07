#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"
#include <unistd.h>
#include <sys/epoll.h>

Channel::Channel(EventLoop *_event_loop, int _fd) : 
    event_loop(_event_loop), 
    fd(_fd), 
    events(0), 
    ready(0), 
    inEpoll(false), 
    useThreadPool(true){}

Channel::~Channel(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Channel::handleEvent(){
    if(ready & (EPOLLIN | EPOLLPRI)){
        if(useThreadPool)
            event_loop->add_threadpool(read_callback);
        else 
            read_callback();
    }
    if(ready & (EPOLLOUT)){
        if(useThreadPool)
            event_loop->add_threadpool(write_callback);
        else
            write_callback();
    }
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
void Channel::useET(){
    events |=EPOLLET;
    //更新当前事件循环的状态
    event_loop->updateChannel(this);
}
uint32_t Channel::getEvents(){
    return events;
}
uint32_t Channel::getReady(){
    return ready;
}

bool Channel::getInEpoll(){
    return inEpoll;
}
void Channel::setInEpoll(bool _in){
    inEpoll = _in;
}
void Channel::set_Ready(uint32_t _ev){
    ready = _ev;
}
void Channel::set_Read_Callback(std::function<void()> _cb){
    read_callback = _cb;
}
void Channel::set_Use_ThreadPool(bool _use){
    useThreadPool= _use;
}