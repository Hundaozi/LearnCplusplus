#include <iostream>
#include <unistd.h>
#include <string.h>
#include "src/util.h"
#include "src/Buffer.h"
#include "src/InetAddress.h"
#include "src/Socket.h"

int main(){
    Socket *sock = new Socket();
    InetAddress *addr = new InetAddress("127.0.0.1", 4490);
    sock->connect(addr);

    int sockfd=sock->get_socket_fd();

    Buffer* sendBuffer= new Buffer();//发送缓冲区
    Buffer* readBuffer= new Buffer();//接受缓冲区

    while(true){
        sendBuffer->getline();//从键盘获取输入
        //客户端写入的数据
        ssize_t client_write_bytes=write(sockfd,sendBuffer->c_str(),sendBuffer->size());
        if(client_write_bytes==-1){
            printf("Socket已经断开连接，无法再发送数据！\n");
            break;
        }
        int already_read = 0;//已读取数
        char buf[1024];//无所谓的大小
        while(true){
            bzero(&buf,sizeof(buf));
            auto client_read_bytes=read(sockfd,buf, sizeof(buf));
            if(client_read_bytes>0){
                readBuffer->append(buf,client_read_bytes);
                already_read +=client_read_bytes;//已经读取的数据
            }else if (client_read_bytes==0)
            {
                printf("服务器断开连接！\n");
                exit(EXIT_SUCCESS);
            }
            if(already_read >= sendBuffer->size()){
                printf("服务器收到 :  %s\n", readBuffer->c_str());
                break;
            }     
        }
        readBuffer->clear();
    }
    delete addr;
    delete sock;
    return 0;
}