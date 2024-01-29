#pragma once

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

#include "safeQueue.h"

class thread_pool{
    private:
        class ThreadWorker{

            private:
                //线程的id
                int thread_id;
                //声明一个指针
                thread_pool *my_pool;
            public:
                //构造
                ThreadWorker(thread_pool *pool,const int id):
                    my_pool(pool),thread_id(id){}
                
                void thread_operator(){
                    std::function<void()> func;
                    bool dequeued; //判断是否出队
                    while(){

                    }
                }
        };
        bool thread_shutdown; //判断线程是否关闭

        safeQueue<std::function<void()>> safequeue;
        std::vector<std::thread> threads;//装有线程类型的向量

        std::mutex mythread_conditional_mutex;//还是互斥锁
        std::condition_variable my_conditional_lock;//条件变量锁

    public:
        //构造，初始线程池中的线程数量，此时没有创建线程
        thread_pool(const int n_threads)
            :threads(std::vector<std::thread>(n_threads)),thread_shutdown(false){

            }
        //不使用默认复制构造
        thread_pool(const thread_pool &)=delete;
        //也不使用默认移动构造
        thread_pool(thread_pool &&)=delete;
        //不使用默认重载赋值
        thread_pool & operator=(const thread_pool&) =delete;
        //也不使用默认重载移动赋值
        thread_pool & operator=(thread_pool &&)= delete;

        //初始化线程池
        void init()
        {
            //初始化i个线程，将线程怼进vector中
            for(auto i=0;i<threads.size(); ++i){
                threads[i]= std::thread(ThreadWorker(this,i));
            }
        }
        //停止线程池工作，一直等待，直到线程完成当前的任务
        void shutdown(){
            thread_shutdown= true;//将flag改成真，意味着该停止等待了

            //notify_one()：因为只唤醒等待队列中的第一个线程；
            //不存在锁争用，所以能够立即获得锁。
            //其余的线程不会被唤醒，需要等待再次调用notify_one()或者notify_all()。

            //notify_all()：会唤醒所有等待队列中阻塞的线程，存在锁争用，只有一个线程能够获得锁。
            //其余未获取锁的线程会继续尝试获得锁，而不会再次阻塞
            my_conditional_lock.notify_all();//线程，启动！

            //++i与i++运行速度一样，但前者的空间使用的更少，总体效率更高
            for(auto i=0;i<threads.size() ;++i){
                if(threads[i].joinable()){
                    //join()函数是一个等待线程完成函数，主线程需要等待子线程运行结束了才可以结束
                    threads[i].join();
                }
            }
        }
};