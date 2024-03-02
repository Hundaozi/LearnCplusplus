#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
    int fd=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serv_addr;

    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.01");
    serv_addr.sin_port=htons(4490);

    //绑定
    bind(fd, (sockaddr*)&serv_addr, sizeof(serv_addr));

    //监听fd
    listen(fd,SOMAXCONN);

    struct sockaddr_in client_addr;

    //typedef __darwin_socklen_t      socklen_t;
    //typedef __uint32_t              __darwin_socklen_t; 
    //typedef unsigned int            __uint32_t;
    //其实就是无符号int型

    socklen_t client_addr_len=sizeof(client_addr);

    bzero(&client_addr, sizeof(client_addr));

    //bind只需要传入serv_addr的大小即可，
    //而accept需要写入客户端socket长度，
    //所以需要定义一个类型为socklen_t的变量，并传入这个变量的地址。
    //另外，accept函数会阻塞当前程序，直到有一个客户端socket被接受后程序才会往下运行。

    int client_fd=accept(fd,(sockaddr*)&client_addr,&client_addr_len);
    //大小端地址转换
    printf("new client fd %d! IP: %s Port: %d\n", client_fd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return 0;

}