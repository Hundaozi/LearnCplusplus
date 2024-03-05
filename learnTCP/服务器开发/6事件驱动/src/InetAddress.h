#pragma once
#include<arpa/inet.h>

//原来C++也是调用C实现的库，这样语言上没有一致性吧？

class InetAddress{
    public:
    //class都是默认私有的
    //struct都默认公有
            //结构体其实很简单。。。。
        struct sockaddr_in addr;
            //struct sockaddr_in
        //   {
        //     __SOCKADDR_COMMON (sin_);
        //     in_port_t sin_port;			/* Port number.  */
        //     struct in_addr sin_addr;		/* Internet address.  */

        //     /* Pad to size of `struct sockaddr'.  */
        //     unsigned char sin_zero[sizeof (struct sockaddr)
        // 			   - __SOCKADDR_COMMON_SIZE
        // 			   - sizeof (in_port_t)
        // 			   - sizeof (struct in_addr)];
        //   };
        
        //socklen_t addr_len;
        socklen_t addr_len;
        InetAddress();
        InetAddress(const char* ip, uint16_t port);
        ~InetAddress();


};
