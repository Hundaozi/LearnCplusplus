#pragma once

#include <map>
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class Server
{
private:
    EventLoop *loop;
    Acceptor *acceptor;
    //用map来存储TCP连接
    std::map<int, Connection*> connections;
public:
    Server(EventLoop*);
    ~Server();

    void handleReadEvent(int);
    void newConnection(Socket *_sock);
    void deleteConnection(int _sock);
};