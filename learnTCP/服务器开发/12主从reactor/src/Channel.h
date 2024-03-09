#pragma once
#include <sys/epoll.h>
#include <functional>
class EventLoop;
class Channel
{
private:
    EventLoop *event_loop;
    int fd;
    uint32_t events;//事件数量
    uint32_t ready;//已就绪数量
    bool inEpoll;//是否在EPOLL中
    //bool useThreadPool;//是否使用了线程池
    std::function<void()> read_callback;
    std::function<void()> write_callback;
public:
    Channel(EventLoop *_loop, int _fd);
    ~Channel();
    void handleEvent();
    void enableReading();

    int getFd();
    uint32_t getEvents();
    uint32_t getReady();

    bool getInEpoll();
    void setInEpoll(bool _in = true);
    
    void useET();

    void set_Ready(uint32_t);
    void set_Read_Callback(std::function<void()>);
    //void set_Use_ThreadPool(bool _use= true);
};