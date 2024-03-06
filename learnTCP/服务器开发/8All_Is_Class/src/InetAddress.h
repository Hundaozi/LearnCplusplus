#pragma once
#include <arpa/inet.h>

//封装了Socket地址
class InetAddress{
    private:
        struct sockaddr_in addr;
        socklen_t addr_len;
    public:
        InetAddress();
        InetAddress(const char* ip, uint16_t port);
        ~InetAddress();
        //设置网络地址和长度
        void setInetAddr(sockaddr_in _addr, socklen_t _addr_len);
        //获取地址
        sockaddr_in getAddr();
        //获取地址的长度
        socklen_t getAddr_len();
};