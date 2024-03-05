#include "InetAddress.h"
#include <string.h>

InetAddress::InetAddress():addr_len(sizeof(addr)){
    bzero(&addr,sizeof(addr));
    //还在用裸指针，有安全隐患

}
InetAddress::InetAddress(const char* ip, uint16_t port) : addr_len(sizeof(addr)){
    bzero(&addr, sizeof(addr));
    addr.sin_family=AF_INET;//ipv4
    addr.sin_addr.s_addr=inet_addr(ip);
    //主机字节序转成16位的网络字节序
    //即大端法
    addr.sin_port=htons(port);
    addr_len=sizeof(addr);

}

InetAddress::~InetAddress(){}