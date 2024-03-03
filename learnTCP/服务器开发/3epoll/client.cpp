#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

int main(){
    int fd= socket(AF_INET,SOCK_STREAM,0);

    errif(fd==-1,"socket 创建错误");
    struct sockaddr_in server_addr;

    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_addr.sin_port=htons(4490);

    errif(connect(fd, (sockaddr*)&server_addr, sizeof(server_addr))==-1,"sockt 连接 失败");

    while(true){
        char buffer[1024];
        bzero(&buffer, sizeof(buffer));
        scanf("%s", buffer);
        ssize_t write_bytes = write(fd, buffer, sizeof(buffer));
        if(write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        bzero(&buffer, sizeof(buffer));
        ssize_t read_bytes = read(fd, buffer, sizeof(buffer));
        if(read_bytes > 0){
            printf("message from server: %s\n", buffer);
        }else if(read_bytes == 0){
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){
            close(fd);
            errif(true, "socket read error");
        }
    }
    //逻辑完成，关闭socket网络
    close(fd);
    return 0;
}

