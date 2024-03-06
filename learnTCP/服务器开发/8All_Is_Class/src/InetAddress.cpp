#include "InetAddress.h"
#include <string.h>

InetAddress::InetAddress() : addr_len(sizeof(addr)){
    /* Set N bytes of S to 0.  */
    bzero(&addr, sizeof(addr));//初始为0
}

InetAddress::InetAddress(const char* ip, uint16_t port) : addr_len(sizeof(addr)){
    bzero(&addr, sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);//设置ip地址
    addr.sin_port=htons(port);//设置端口
    addr_len=sizeof(addr);//设置地址的长度
}
//使用默认的析构函数
InetAddress::~InetAddress(){}

//设置网络地址
void InetAddress::setInetAddr(sockaddr_in _addr, socklen_t _addr_len){
    addr=_addr;
    addr_len=_addr_len;
}

//获取地址
sockaddr_in InetAddress::getAddr(){
    return addr;
}
//获取地址长度
socklen_t InetAddress::getAddr_len(){
    return addr_len;
}