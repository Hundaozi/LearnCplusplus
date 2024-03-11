#include "include/ThreadPool.h"
#include <mutex>
#include <thread>

ThreadPool::ThreadPool(unsigned int size){
    for(unsigned int i=0;i<size;++i){
        //匿名函数通过this捕获的结果其实是引用的
        workers_.emplace_back(std::thread([this](){
            while(true){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex_);
                    condition_variable_.wait(lock,[this](){
                        //判断条件为 线程池停止或者任务队列不空
                        return stop_ || !tasks_.empty();
                    });
                        //只有线程池停止和任务队列为空的时候
                    if(stop_ && tasks_.empty()){
                        return ;
                    }
                        //取任务函数
                        task=tasks_.front();
                        tasks_.pop();
                    }
                    task();
                }
        }));
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_=true;
    }
    condition_variable_.notify_all();//唤醒所有等待的线程
    for(std::thread &th : workers_){
        if (th.joinable()) {
            th.join();
        }
    }
}