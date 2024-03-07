#pragma once
#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

//之前就写过了，线程池是为了分配线程的，先初始化一定数量的线程，然后分配任务

class ThreadPool
{
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex tasks_mtx;
    std::condition_variable cv;
    bool stop;
public:
    ThreadPool(int size = 10);
    ~ThreadPool();

    template<class F, class... Args>
    //C++14
    decltype(auto) add(F&& f, Args&&... args);
    //C++11
    //auto ThreadPool::add(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>

};
//不能放在cpp文件，原因是C++编译器不支持模版的分离编译
template<class F, class... Args>
decltype(auto) 
add(F&& f, Args&&... args){
    //获取函数返回值的类型
    using return_type= typename std::result_of_t<F(Args...)>::type;
    //packaged_task：将一个普通的可调用函数对象转换为异步执行的任务
    auto task=std::make_shared<std::packaged_task<return_type>> (
        std::bind(
            //完美转发只是确保左右值的属性
            //核心概念是引用折叠的静态转换
            //左值还是左值，右值还是右值
            std::forward<F>(f),
            std::forward<Args>(args)...)
    )
    //std::future类模板来关联线程运行的函数和函数的返回结果，这种获取结果的方式是异步的。
    std::future<return_type> res=task->get_future();
    {
        std::unique_lock<std::mutex> lock(tasks_mtx);

        if(stop){
            throw std::runtime_error("错误，询问已停止的线程池");
        }
        //tasks是任务队列
        //task是一个智能指针，本质上是函数指针，指向了可以被打包后可以异步执行的任务函数
        tasks.emplace([task](){
            //按值捕获，这个值是指针
            //解引用，执行任务函数
            (*task)();
        });
    }
    cv.notify_one();
    return res;
}