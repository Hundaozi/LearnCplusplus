#pragma once
#include <functional>

class EventLoop;
class Socket;
class Channel;
//将TCP连接封装成一个类
class Connection{
    private:
        EventLoop *loop;
        Socket *sock;
        Channel *channel;
        //删除TCP的回调函数
        std::function<void(Socket*)> deleteConnectionCallback;
    public:
        Connection(EventLoop *_loop, Socket *_sock);
        ~Connection();
        void echo(int _sockfd);
        void setDeleteConnectionCallback(std::function<void(Socket*)>);
};