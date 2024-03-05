#pragma once

class Epoll;
class Channel;
class EventLoop{
    private:
        Epoll *ep;
        bool quit;//判断是否退出的标识符
    public:
        EventLoop();
        ~EventLoop();

        void loop();
        void updateChannel(Channel*);
};