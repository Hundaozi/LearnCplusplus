#include "Channel.h"
#include "Epoll.h"

Channel::Channel(Epoll *_ep, int _fd) : ep(_ep), fd(_fd), events(0), revents(0), inEpoll(false){

}

Channel::~Channel()
{
}

void Channel::enableReading(){
    events= EPOLLIN | EPOLLET;//水平触发和边缘触发
    ep->updateChannel(this);//修改当前的Channel
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
