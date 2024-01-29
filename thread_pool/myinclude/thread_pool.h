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
                //
                thread_pool *my_pool;
            public:
                //构造
                ThreadWorker(thread_pool *pool,const int id):
                    my_pool(pool),thread_id(id){}
                
                //对线程的操作
                void thread_operator(){
                   
                    /*
                        std::function的实例可以存储、复制和调用任何可复制构造的可调用目标
                        包括普通函数、成员函数、类对象（重载了operator()的类的对象）、Lambda表达式等
                        是对C++现有的可调用实体的一种类型安全的包裹（相比而言，函数指针这种可调用实体，是类型不安全的）。
                    */
                    std::function<void()> func;
                    bool dequeued; //判断是否出队
                    while(!my_pool->thread_shutdown){
                        //unique_lock 的成员函数 lock() 上锁后，在对象析构的时候会自动解锁
                        std::unique_lock<std::mutex> lock(my_pool->mythread_conditional_mutex);
                        //如果任务队列是空的，加锁，让其等待
                        if(my_pool->safequeue.empty())
                        {
                            my_pool->my_conditional_lock.wait(lock);
                        }
                        //判断fun函数是否出入队
                        dequeued=my_pool->safequeue.dequeue(func);
                        //已入队，执行任务函数
                        if(dequeued){
                            func();
                        }
                    }
                }
        };
        bool thread_shutdown; //判断线程是否关闭

        //定义一个装有任务函数的队列
        safeQueue<std::function<void()>> safequeue;
        std::vector<std::thread> threads;//装有线程类型的向量

        std::mutex mythread_conditional_mutex;//互斥锁
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
                //this指向线程池
                //要初始化的线程数量为i个
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
                //如果线程可加入
                if(threads[i].joinable()){
                    //join()函数是一个等待线程完成函数，主线程需要等待子线程运行结束了才可以结束
                    threads[i].join();
                }
            }
        }
        //提交要由池异步执行的函数
        template<typename F, typename...Args>
        //自动推导返回值类型,C++14标准
        decltype(auto)
        submit(F&& f, Args&&... args){
            
            //创建一个具有可执行的有界参数的函数
            std::function<decltype(f(args...))()> func= std::bind(std::forward<F>(f), std::forward<Args>(args)...);

            //将其封装在共享指针中，让它能够复制构造和赋值
            //packaged_task，故名思义打包任务
            //是用来进行任务封装的，即将任务封装起来
            //将任务封装起来的目的是为了进行线程之间的传递，进行任务的异步处理
            auto task_ptr= std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
            /*
            在主线程中，通过packaged_task类模版对可调用对象进行封装，封装成一个packaged_task对象
            通过调用packaged_task可调用对象的get_future函数，
            获取对应的future对象，用来之后获取异步调用的结果信息
            将该packaged_task对象交给其他线程执行
            其他线程执行该packaged_task可调用对象
            在packaged_task可调用对象执行过程中，
            对内部存储的异步操作对应的可操作对象进行函数调用。
            调用完成之后，将调用结果信息设置到共享状态对象中
            主线程中通过调用future对象的get成员函数，
            从其关联的共享状态对象中获取异步调用的结果信息。
            如果此时异步调用已经执行完成，则该函数立刻返回异步调用结果信息。
            如果没有执行完成，此时将阻塞，直到异步调用执行完成
            */

            //将打包的任务包装到void函数中
            //捕获任务指针
            std::function<void()> wrapper_func=[task_ptr](){
                //解引用，取对象
                //取到的对象是packaged_task
                //packaged_task里面装着要运行的任务函数
                (*task_ptr)();
            }

            //将这些任务函数入队
            safequeue.enqueue(wrapper_func);

            //如果一个线程在等待，唤醒它
            my_conditional_lock.notify_one();

            //从promise中返回future
            return task_ptr->get_future();
        }
};