#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include <vector>

EventLoop::EventLoop():ep(nullptr){
    ep =new Epoll();
    //new一个epoll
    //懂了，loop就是再次将epoll包装，同时附加上一些函数，这些函数方便我们操作和处理
    
}

EventLoop::~EventLoop()
{
    delete ep;
    //删除
}
void EventLoop::loop(){
    while(!quit){
        std::vector<Channel*> chs;
        chs=ep->poll();//挂载事件
        for(auto it=chs.begin();it!=chs.end();++it){
            (*it)->handleEvent();//依次处理事件
        }

    }
}
void EventLoop::updateChannel(Channel *ch){
    //就是将Channel传进去
    ep->updateChannel(ch);//哦哦，套娃
}