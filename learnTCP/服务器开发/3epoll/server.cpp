#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

int main(){

    int fd=socket(AF_INET,SOCK_STREAM,0);
    errif(fd==-1,"socket 创建错误");

    struct sockaddr_in server_addr;
    //void	 bzero(void *, size_t) __POSIX_C_DEPRECATED(200112L);
    //传一个指针，然后是大小，后面的参数，有点不懂。。。200112L?
    //#define __POSIX_C_DEPRECATED(ver) ___POSIX_C_DEPRECATED_STARTING_##ver
    bzero(&server_addr,sizeof(server_addr));

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.01");
    //#define htons(x)        __DARWIN_OSSwapInt16(x)
    server_addr.sin_port=htons(4490);

    errif(bind(fd,(sockaddr*)&server_addr,sizeof(server_addr))==-1,"socket bind错误");

    //原来如此，侦听可指定的最大队列长度。
    errif(listen(fd,SOMAXCONN)==-1,"socket listen 错误");
    //
    /*
    * Maximum queue length specifiable by listen.
    */
    //#define SOMAXCONN       128

    struct sockaddr_in client_addr;
    //unsigned int 类型
    socklen_t client_addr_len=sizeof(client_addr);
    //bzero()函数用于将一段内存区域清零，即将这段内存区域中的所有字节都设置为0。
    //原来如此，终于懂了
    bzero(&client_addr,sizeof(client_addr));

    //accept的函数原型
    //三个参数，一个int，两个指针
    //int accept(int, struct sockaddr * __restrict, socklen_t * __restrict)
    int client_fd=accept(fd,(sockaddr*)&client_addr,&client_addr_len);

    errif(client_fd==-1, "socket accept error");
    printf("new client fd %d! IP: %s Port: %d\n", client_fd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    //如果接受成功，开始处理数据
    //当我们建立一个socket连接后
    //就可以使用<unistd.h>头文件中read和write来进行网络接口的数据读写操作了。

    while (true) {
        char buffer[1024];
        bzero(&buffer, sizeof(buffer));
        ssize_t read_bytes = read(client_fd, buffer, sizeof(buffer));
        if(read_bytes > 0){
            printf("message from client fd %d: %s\n", client_fd, buffer);
            write(client_fd, buffer, sizeof(buffer));
        } else if(read_bytes == 0){
            printf("client fd %d disconnected\n", client_fd);
            close(client_fd);
            break;
        } else if(read_bytes == -1){
            close(client_fd);
            errif(true, "socket read error");
        }
    }
    close(fd);
    return 0;


}
