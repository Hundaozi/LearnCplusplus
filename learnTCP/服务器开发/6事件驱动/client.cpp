#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "src/util.h"
#define BUFFER_SIZE 1024
//第一步，设置fd
//第二步，设置服务器的连接信息
//第三步，开搞，连接服务器
//第四五，通讯
//第六步，关闭socket
int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);

    errif(sockfd == -1, "socket create error");

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(4490);

    errif(connect(sockfd,(sockaddr*)&server_addr, sizeof(server_addr))==-1,"socket connect error");

    while(true){
        //老三样，缓冲，初始化缓冲区，写操作
        char buffer[BUFFER_SIZE];
        bzero(&buffer,sizeof(buffer));
        ssize_t write_bytes =write(sockfd,buffer,sizeof(buffer));
        
        if(write_bytes==-1){
            //写不了
            printf("socket already disconnected, can't write any more!\n");
            break;

        }
        
        //写完之后再读取.
        //等等，按道理应该两个缓冲区一读一写的，现在用一个buffer，还有优化的空间
        bzero(&buffer,sizeof(buffer));
        //再次清空缓冲区，然后从服务端读取数据
        ssize_t read_bytes= read(sockfd,buffer,sizeof(buffer));

        if(read_bytes>0){
            //如果读取成功
            //接下来是一系列的操作,不会写，先搞个消息输出
            printf("message from server: %s\n", buffer);
        }else if(read_bytes==0){
            //空的
            printf("server socket disconnected!\n");
            break;

        }else if (read_bytes == -1)
        {
            /* code */
            //读取出错，断开连接
            close(sockfd);
            errif(true, "socket read error");
        }
        
    }
    close(sockfd);
    return 0;


}