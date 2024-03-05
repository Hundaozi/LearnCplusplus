Server作为一个服务器类，应该更抽象、更通用，我们应该对服务器进行进一步的模块化。

所谓的acceptor，接收器，就是分配连接的。


首先要初始化socket，然后将其初始化。
都是要通过accept()接受
然后再将文件描述符fd添加到epoll树上
当这个IO口有事件发生的时候，再对此TCP连接提供相应的服务。
这就是TCP，面向连接的意思

这个接收器应该存在于EventLoop之中，就是在main-Reactor中
每一个接收器对应一个fd
再通过Channel分配到epoll树上

就是将新建网络连接的逻辑封装在接收器中
Sever负责创建socket,管理它的生命周期，不是Acceptor做的。
接收器是负责管理建立连接的
