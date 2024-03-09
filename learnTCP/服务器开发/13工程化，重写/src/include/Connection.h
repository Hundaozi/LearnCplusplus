#pragma once
#include "Macros.h"
#include <functional>

class EventLoop;
class Socket;
class Channel;
class Buffer;
//TCP连接类
class Connection {
    public:
        Connection(EventLoop *loop, Socket *sock);
        ~Connection();
        DISALLOW_COPY_AND_MOVE(Connection);
        //输出
        void Echo(int sockfd);
        //设置删除TCP连接实例的回调函数
        void SetDeleteConnectionCallback(std::function<void(int)> const &callback);
        //发送
        void Send(int sockfd);

    private:
        EventLoop *loop_;
        Socket *sock_;
        Channel *channel_;
        std::function<void(int)> delete_connectioin_callback_;
        Buffer *read_buffer_;
};