#pragma once
#include <sys/epoll.h>
#include <vector>

class Channel;
class Epoll{
    private:
        int epoll_fd;
        struct epoll_event *epoll_events;
    public:
        Epoll();
        ~Epoll();
        void updateChannel(Channel*);
        void deleteChannel(Channel*);
        
        std::vector<Channel*> poll(int _timeout = -1);
};