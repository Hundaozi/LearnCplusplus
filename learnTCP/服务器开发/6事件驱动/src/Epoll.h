#pragma once
#include <sys/epoll.h>
#include <vector>
class Channel;
class Epoll{
    private:
        int epfd;
        struct epoll_event *events;
    
    public:
        Epoll();
        ~Epoll();
        void updateChannel(Channel*);
        void add_fd(int fd, uint32_t op);
        //std::vector<epoll_event> poll(int timeout = -1);
        std::vector<Channel*> poll(int timeout = -1);
};