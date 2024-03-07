#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include "threadpool.h"
#include <vector>

EventLoop::EventLoop() : ep(nullptr), threadpool(nullptr),quit(false){
    ep = new Epoll();
    threadpool = new ThreadPool();
}

EventLoop::~EventLoop()
{
    delete threadpool;
    delete ep;
}

//事件循环
void EventLoop::loop(){
    while(!quit){
    std::vector<Channel*> chs;
        chs = ep->poll();
        for(auto it = chs.begin(); it != chs.end(); ++it){
            (*it)->handleEvent();
        }
    }
}
//更新Channel
void EventLoop::updateChannel(Channel *_ch){
    ep->updateChannel(_ch);
}
//将任务函数添加到线程池中
void EventLoop::add_threadpool(std::function<void()> _func){
    threadpool->add(_func);
}