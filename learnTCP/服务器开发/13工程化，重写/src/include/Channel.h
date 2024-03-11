#pragma once
#include "Macros.h"

#include <functional>

class Socket;
class EventLoop;
class Channel {
    public:
        Channel(EventLoop *loop, int fd);
        ~Channel();

        DISALLOW_COPY_AND_MOVE(Channel);
        //处理事件
        void HandleEvent();
        //可读取
        void EnableRead();
        //获取fd
        int GetFd();
        //获取监听事件
        uint32_t GetListenEvents();
        //获取就绪事件
        uint32_t GetReadyEvents();
        //flag：是否在Epoll
        bool GetInEpoll();
        //设置是否在Epoll
        void SetInEpoll(bool in = true);
        //使用边缘触发模式
        void UseET();
        //设置就绪事件
        void SetReadyEvents(uint32_t ev);
        //设置读取回调函数
        void SetReadCallback(std::function<void()> const &callback);

    private:
        EventLoop *loop_;
        int fd_;
        uint32_t listen_events_;//监听中的事件数量
        uint32_t ready_events_;//已就绪的事件数量
        bool in_epoll_;//是否在epoll红黑树中
        //读取回调函数
        std::function<void()> read_callback_;
        //写入回调函数
        std::function<void()> write_callback_;
};