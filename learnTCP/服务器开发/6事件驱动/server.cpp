#include "src/EventLoop.h"
#include "src/Server.h"

int main(){
    EventLoop *loop=new EventLoop();
    Server * server=new Server(loop);
    loop->loop();
    return 0;

    //Epoll将linux底层的epoll库封装
    //Eventloop将Epoll封装
    //Channel再将Eventloop封装

    //server最后封装了Channel
}