#pragma once
#include <arpa/inet.h>
#include "Macros.h"
class InetAddress {
    public:
        InetAddress();
        InetAddress(const char *ip, uint16_t port);
        ~InetAddress() = default;

        DISALLOW_COPY_AND_MOVE(InetAddress);

        void SetAddr(sockaddr_in addr);
        sockaddr_in GetAddr();
        const char *GetIp();
        uint16_t GetPort();

    private:
        struct sockaddr_in addr_ {};
};

class Socket {
    private:
        //Socket文件描述符
        int fd_{-1};

    public:
        Socket();
        explicit Socket(int fd);
        ~Socket();

        DISALLOW_COPY_AND_MOVE(Socket);

        //绑定
        void Bind(InetAddress *addr);
        //监听
        void Listen();
        //接受
        int Accept(InetAddress *addr);
        //连接
        void Connect(InetAddress *addr);
        //设置为非阻塞
        void SetNonBlocking();
        //获取文件描述符
        int GetFd();
};