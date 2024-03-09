#include <iostream>
#include <unistd.h>
#include <string.h>
#include <functional>
#include "src/Buffer.h"
#include "src/Socket.h"
#include "src/threadpool.h"
#include "src/util.h"

void oneClient(int _msgs, int _wait){
    Socket *sock = new Socket();
    InetAddress *addr = new InetAddress("127.0.0.1", 4490);
    // sock->setnonblocking(); 客户端使用阻塞式连接比较好，方便简单不容易出错
    sock->connect(addr);

    int sockfd = sock->get_socket_fd();

    Buffer *sendBuffer = new Buffer();
    Buffer *readBuffer = new Buffer();

    sleep((int)_wait);
    int count = 0;
    while(count < _msgs){
        sendBuffer->setBuf("I'm client!");
        ssize_t write_bytes = write(sockfd, sendBuffer->c_str(), sendBuffer->size());
        if(write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        int already_read = 0;
        char buf[1024];    //这个buf大小无所谓
        while(true){
            bzero(&buf, sizeof(buf));
            ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
            if(read_bytes > 0){
                readBuffer->append(buf, read_bytes);
                already_read += read_bytes;
            } else if(read_bytes == 0){         //EOF
                printf("server disconnected!\n");
                exit(EXIT_SUCCESS);
            }
            if(already_read >= sendBuffer->size()){
                printf("count: %d, message from server: %s\n", count++, readBuffer->c_str());
                break;
            } 
        }
        readBuffer->clear();
    }
    delete addr;
    delete sock;
}

int main(int argc, char *argv[]) {
    int threads = 100;
    int msgs = 100;
    int wait = 0;
    int o;
    const char *optstring = "t:m:w:";
    while ((o = getopt(argc, argv, optstring)) != -1) {
        switch (o) {
            case 't':
                threads = std::stoi(optarg);
                break;
            case 'm':
                msgs = std::stoi(optarg);
                break;
            case 'w':
                wait = std::stoi(optarg);
                break;
            case '?':
                printf("error optopt: %c\n", optopt);
                printf("error opterr: %d\n", opterr);
                break;
        }
    }

    ThreadPool *poll = new ThreadPool(threads);
    std::function<void()> func = std::bind(oneClient, msgs, wait);
    for(int i = 0; i < threads; ++i){
        poll->add(func);
    }
    delete poll;
    return 0;
}