
这个是源码中的epoll数据结构

typedef union epoll_data {
  void *ptr;
  int fd;
  uint32_t u32;
  uint64_t u64;
} epoll_data_t;
struct epoll_event {
  uint32_t events; /* Epoll events */
  epoll_data_t data; /* User data variable */
} __EPOLL_PACKED;

实际上就是一个联合体，存储了指针和fd
通过指针，可以指向任何东西
将一个文件描述符封装成一个Channel类，这样这个类的实例就只负责一个fd
对于不同的服务和事件类型，都可以用在类中定义好不同的处理，这样就得到更多的功能，而不是仅仅只拿一个文件描述符fd。

在C++17中已经用 variant，变体，取代了联合体union
variant不仅速度更快，最主要是有了类型检查
std::variant 是类型安全的，只能访问一种类型
