#pragma once
#include "Macros.h"

#include <functional>

class EventLoop;
class Socket;
class Channel;
//接收器类
class Acceptor {
    public:
        explicit Acceptor(EventLoop *loop);
        ~Acceptor();

        DISALLOW_COPY_AND_MOVE(Acceptor);
        //接受TCP连接实例
        void AcceptConnection();
        //设置新TCP连接实例的回调函数
        void SetNewConnectionCallback(std::function<void(Socket *)> const &callback);

    private:
        EventLoop *loop_;
        Socket *sock_;
        Channel *channel_;
        std::function<void(Socket *)> new_connection_callback_;
};