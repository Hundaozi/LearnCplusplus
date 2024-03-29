#include "include/Socket.h"
#include "include/util.h"
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket() {
  //默认使用TCP
  fd_ = socket(AF_INET, SOCK_STREAM, 0);
  ErrorIf(fd_ == -1, "socket create error");
}

Socket::Socket(int fd) : fd_(fd) { ErrorIf(fd_ == -1, "socket create error"); }

Socket::~Socket() {
  if (fd_ != -1) {
    close(fd_);
    fd_ = -1;
  }
}
// socket绑定
void Socket::Bind(InetAddress *addr) {
  struct sockaddr_in tmp_addr = addr->GetAddr();
  ErrorIf(bind(fd_, (sockaddr *)&tmp_addr, sizeof(tmp_addr)) == -1,
          "socket bind error");
}
// socket 监听
void Socket::Listen() {
  ErrorIf(::listen(fd_, SOMAXCONN) == -1, "socket listen error");
}

//设置为非阻塞模式
void Socket::SetNonBlocking() {
  fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK);
}

// socket 接受
int Socket::Accept(InetAddress *addr) {
  // for server socket
  int client_sock_fd = -1;
  struct sockaddr_in tmp_addr {};
  socklen_t addr_len = sizeof(tmp_addr);
  if (fcntl(fd_, F_GETFL) & O_NONBLOCK) {
    while (true) {
      client_sock_fd = accept(fd_, (sockaddr *)&tmp_addr, &addr_len);
      if (client_sock_fd == -1 &&
          ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {
        continue;
      }
      if (client_sock_fd == -1) {
        ErrorIf(true, "socket accept error");
      } else {
        break;
      }
    }
  } else {
    client_sock_fd = accept(fd_, (sockaddr *)&tmp_addr, &addr_len);
    ErrorIf(client_sock_fd == -1, "socket accept error");
  }
  addr->SetAddr(tmp_addr);
  return client_sock_fd;
}
//连接函数
void Socket::Connect(InetAddress *addr) {
  // for client socket
  struct sockaddr_in tmp_addr = addr->GetAddr();
  if (fcntl(fd_, F_GETFL) & O_NONBLOCK) {
    while (true) {
      auto ret = connect(fd_, (sockaddr *)&tmp_addr, sizeof(tmp_addr));
      if (ret == 0) {
        break;
      }
      if (ret == -1 && (errno == EINPROGRESS)) {
        continue;
        /* 连接非阻塞式sockfd建议的做法：
        The socket is nonblocking and the connection cannot be
        completed immediately.  (UNIX domain sockets failed with
        EAGAIN instead.)  It is possible to select(2) or poll(2)
        for completion by selecting the socket for writing.  After
        select(2) indicates writability, use getsockopt(2) to read
        the SO_ERROR option at level SOL_SOCKET to determine
        whether connect() completed successfully (SO_ERROR is
        zero) or unsuccessfully (SO_ERROR is one of the usual
        error codes listed here, explaining the reason for the
        failure).
        这里为了简单、不断连接直到连接完成，相当于阻塞式
        */
      }
      if (ret == -1) {
        ErrorIf(true, "socket connect error");
      }
    }
  } else {
    ErrorIf(connect(fd_, (sockaddr *)&tmp_addr, sizeof(tmp_addr)) == -1,
            "socket connect error");
  }
}
//获取文件标识符
int Socket::GetFd() { return fd_; }

InetAddress::InetAddress() = default;

InetAddress::InetAddress(const char *ip, uint16_t port) {
  /* Set N bytes of S to C.  */
  memset(&addr_, 0, sizeof(addr_));
  addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = inet_addr(ip);
  addr_.sin_port = htons(port);
}

void InetAddress::SetAddr(sockaddr_in addr) { addr_ = addr; }

//获取网络地址
sockaddr_in InetAddress::GetAddr() { return addr_; }
//获取网络ip地址
const char *InetAddress::GetIp() { return inet_ntoa(addr_.sin_addr); }
//获取网络端口
uint16_t InetAddress::GetPort() { return ntohs(addr_.sin_port); }