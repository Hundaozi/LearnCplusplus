
所有的服务器都是高并发服务器，为了处理成千上万甚至上百万的并发
虽然现在的服务器都是有负载均衡的分布式服务器
但要为这么多的客户端提供服务，每个服务节点的压力也是十分巨大的
所以需要使用IO复用。

IO复用与多线程相似，都是并发技术。
IO复用针对于接口，而多线程针对CPU
虽然最后都是CPU进行处理。

IO复用的基本思想是事件驱动。
所谓事件，就是有读写事件。
服务器保持多个客户端的IO连接，每当这个IO上有读写事情发生时，表示这个IO对应的客户端在请求服务器的某项服务，此时服务器响应该服务。

Linux系统中，IO复用使用select, poll和epoll来实现。

epoll是Linux上特有的，Windows（暂时没用过。应该可以用C++库来搞定）

Linux系统在访问设备的时候，存在以下几种IO模型：

Blocking IO Model，阻塞IO模型；
Nonblocking I/O Model，非阻塞IO模型；
I/O Multiplexing Model，IO多路复用模型;
Signal Driven I/O Model，信号驱动IO模型；
Asynchronous I/O Model，异步IO模型；

elect,poll,epoll都是IO多路复用的机制，监视多个描述符，一旦某个描述符就绪，通知程序进行操作。
时间复杂度：
    select：O(n)
    poll：O(n)
    epoll：O（1）
最大支持文件描述符fd数量：
    select：1024
    poll：65535
    epoll：65535
工作模式：
    select：LT（水平触发）
    poll：LT
    epoll：LT和ET（边缘触发）

底层实现原理：

    select 和 poll 都是采用轮询的方式，即每次调用都要扫描整个注册的文件描述符，并将其中就绪文件描述符的数量返回给应用程序，因此它们检测就绪文件描述符的事件复杂度为O(n)。

    而epoll则不同，它采用的是回调的方式，内核检测到就绪的文件描述符时，将触发回调函数，回调函数就将该文件描述符上对应的事件插入到内核就绪事件队列。当调用epoll_wait 系统调用时，无须轮询整个内核事件表中的文件描述符，而只需检测就绪事件队列是否有内容，如有，内核则将该就绪队列中的内容拷贝到用户空间，因此epoll检测就绪文件描述符的时间复杂度为O(1)。

适用场景：

    select、poll：适合在连接数少并且连接都十分活跃的情况下。

    epoll：适用在连接数很多，活跃连接较少的情况下。