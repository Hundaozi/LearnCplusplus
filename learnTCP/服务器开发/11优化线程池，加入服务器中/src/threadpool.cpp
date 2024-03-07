#include "threadpool.h"

ThreadPool::ThreadPool(int size) : stop(false){
    for(int i = 0; i < size; ++i){
        threads.emplace_back(std::thread([this](){
            while(true){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(tasks_mtx);
                    cv.wait(lock, [this](){
                        return stop || !tasks.empty();
                    });
                    if(stop && tasks.empty()) return;
                    task = tasks.front();
                    tasks.pop();
                }
                //我是真的无语，都是从C++并发编程里搞下来的
                task();
            }
        }));
    }
}

ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        stop = true;
    }
    cv.notify_all();
    for(std::thread &th : threads){
        if(th.joinable())
            th.join();
    }
}

void ThreadPool::add(std::function<void()> func){
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);
        if(stop)
            throw std::runtime_error("线程池已经停止，无法再加入任务！");
        tasks.emplace(func);
    }
    cv.notify_one();
}