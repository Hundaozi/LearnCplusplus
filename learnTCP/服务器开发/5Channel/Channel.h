#pragma once
#include <sys/epoll.h>

class Epoll;
//

class Channel{
    private:
        Epoll *ep;
        //一直找不到错误，原来是写成op了，原神你罪该万死
        int fd;
        uint32_t events;
        uint32_t revents;
        bool inEpoll;
    public:
        Channel(Epoll *_ep, int _fd);
        ~Channel();
        void enableReading();
        int get_fd();
        uint32_t getEvents();
        uint32_t getRevents();
        bool getInEpoll();//获取判断
        void setInEpoll();
        void setRevents(uint32_t);
};