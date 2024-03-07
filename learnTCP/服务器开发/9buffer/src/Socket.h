#pragma once

class InetAddress;
class Socket{
    private:
        int socket_fd;
    public:
        Socket();
        Socket(int _socket_fd);
        ~Socket();
        //绑定地址
        void bind(InetAddress*);
        //监听
        void listen();
        //设置非阻塞模式
        void setnonblocking();
        //从特定网络地址和端口接受数据
        int accept(InetAddress*);
        //获取Socket文件描述符
        int get_socket_fd();
        void connect(InetAddress*);
};