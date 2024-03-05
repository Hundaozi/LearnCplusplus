#include "Channel.h"
#include "EventLoop.h"

Channel::Channel(EventLoop *_loop, int _fd) : loop(_loop), fd(_fd), events(0), revents(0), inEpoll(false){

}

Channel::~Channel()
{
}

void Channel::handleEvent(){
    callback();
}

void Channel::enableReading(){
    events= EPOLLIN | EPOLLET;//水平触发和边缘触发
    loop->updateChannel(this);//将ep换成事件循环loop了
}
int Channel::get_fd(){
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
    inEpoll=true;//表示在红黑树中了
}

void Channel::setRevents(uint32_t _ev){
    revents=_ev; //设置事件数量
}

//哦哦，就是简单的打包了一下
void Channel::setCallback(std::function<void()> _cb){
    callback= _cb;
}
