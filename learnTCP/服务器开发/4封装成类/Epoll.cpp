#include "Epoll.h"
#include "util.h"
#include <unistd.h>
#include <string.h>

#define MAX_EVENTS 1000

Epoll::Epoll(): epfd(-1), events(nullptr){
    epfd=epoll_create1(0);
    errif(epfd == -1, "epool create 错误 ");
    //应该用智能指针
    events = new epoll_event[MAX_EVENTS];
    bzero(events, sizeof(*events)*MAX_EVENTS);
}

Epoll::~Epoll(){
    if(epfd !=-1){
        //原来如此，强制停止
        close(epfd);
        epfd=-1;
    }
    delete[] events;
}

void Epoll::add_fd(int fd, uint32_t op){
    struct epoll_event ev;
    bzero(&ev,sizeof(ev));
    ev.data.fd=fd;
    ev.events=op;
    errif(epoll_ctl(epfd,EPOLL_CTL_ADD, fd, &ev) == -1, "epoll 添加 事件 错误");
}


std::vector<epoll_event> Epoll::poll(int timeout){
    std::vector<epoll_event> activeEvents;//活跃事件
    int nfds=epoll_wait(epfd, events, MAX_EVENTS, timeout);
    errif(nfds == -1, "epoll wait 错误");

    //可以换成用容器搞成迭代器插入
    for(auto i=0;i<nfds;++i){
        //activeEvents.push_back(events[i]);
        //push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；
        //而emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
        activeEvents.emplace_back(events[i]);
    }
    return activeEvents;
}