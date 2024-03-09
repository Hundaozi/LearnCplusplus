#pragma once
#include <map>
#include <vector>
class EventLoop;
class Socket;
class Acceptor;
class Connection;
class ThreadPool;
class Server
{
private:
    EventLoop *main_Reactor;//主Reactor
    Acceptor *acceptor;
    //用map来存储TCP连接
    std::map<int, Connection*> connections;
    std::vector<EventLoop*> sub_Reactors;//子Reactor，用来存储任务函数
    ThreadPool *threadpool;
public:
    Server(EventLoop*);
    ~Server();

    void handleReadEvent(int);
    void newConnection(Socket *_sock);
    void deleteConnection(int _sock);
};