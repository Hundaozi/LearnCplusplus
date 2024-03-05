#pragma once

class InetAddress;//少导一次，不过C++20里有import了
class Socket{
    private:
        int fd;
    public:
        Socket();
        Socket(int);
        ~Socket();

        
        void bind(InetAddress*);
        void listen();
        void setnonblocking();
        int accept(InetAddress*);
        int get_fd();
};