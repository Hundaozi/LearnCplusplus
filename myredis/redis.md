use C and C++ code redis

socket()系统调用返回一个fd
fd是一个整数,它指向了linux内核中的某些东西,如:
TCP连接,
disk文件,
监听的端口,
或者其他一些资源

bind()和listen()这两个系统调用:
bind将地址和一个socket fd关联起来
listen 能够确保我们连接到bind的那个地址

accept() 给了一个正在监听中的 fd

当一个客户端产生一个对监听地址的连接
accept可以返回一个fd:这个fd代表着连接的socket


server的工作流:


fd = socket()
bind(fd, address)
listen(fd)

while true:
	conn_fd = accept(fd)
	do_something_with(conn_fd)
	close(conn_fd)


client的工作流:

fd = socket()
connect(fd, address)
do_something_with(fd)
close(fd)
