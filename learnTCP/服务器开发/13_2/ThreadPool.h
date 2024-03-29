#pragma once
#include "Macros.h"
#include <condition_variable> // NOLINT
#include <functional>
#include <future> // NOLINT
#include <memory>
#include <mutex> // NOLINT
#include <queue>
#include <thread> // NOLINT
#include <utility>
#include <vector>
class ThreadPool {
public:
  //阻止隐式转换
  explicit ThreadPool(unsigned int size = std::thread::hardware_concurrency()); //这个函数会返回能并发在一个程序中的线程数量。
  ~ThreadPool();

  //不允许复制也不允许移动
  //DISALLOW_COPY_AND_MOVE(ThreadPool);
  template <class F, class... Args>
  auto Add(F &&f, Args &&... args)
      -> std::future<typename std::result_of<F(Args...)>::type>;

private:
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> tasks_;
  std::mutex queue_mutex_;
  std::condition_variable condition_variable_;
  bool stop_{false};
};

// 不能放在cpp文件，C++编译器不支持模版的分离编译
template <class F, class... Args>
auto ThreadPool::Add(F &&f, Args &&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
  using return_type = typename std::result_of<F(Args...)>::type;

  auto task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...));

  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(queue_mutex_);

    // don't allow enqueueing after stopping the pool
    if (stop_) {
      throw std::runtime_error("错误，无法访问已经停止的线程池！\n");
    }

    tasks_.emplace([task]() { (*task)(); });
  }
  condition_variable_.notify_one();
  return res;
}