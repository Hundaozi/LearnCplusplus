#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<condition_variable>
#include<queue>
#include<vector>
#include<functional>

class threadpool
{
private:
    /* data */

    std::vector<std::thread> threads;//线程数组
    std::queue<std::function<void()>> tasks;//任务队列

    std::mutex mtx;
    std::condition_variable condition;

    bool stop;//判断线程池是否停止
public:
    //numOfthreads : 指定初始化的线程数量
    threadpool(int numOfthreads):stop(false)
    {
        for(auto i=0; i<numOfthreads; ++i){
            //thread类禁止拷贝构造和拷贝赋值
            threads.emplace_back([this]{
                while (1)
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    condition.wait(lock,[this]{
                        return !tasks.empty()//如果不空，不阻塞
                        || stop;
                    });
                    //如果停止工作，或者任务队列为空，则停止
                    if(stop && tasks.empty()){
                        return ;//
                    }
                    //将任务打包成function对象
                    std::function<void()> task(std::move(tasks.front()));
                    tasks.pop();
                    //任务弹出，手动解锁
                    lock.unlock();
                    task();
                }
                
            });
        }
    }
    ~threadpool()
    {   
        {
            std::unique_lock<std::mutex> lock(mtx);//加锁
            stop=true;//线程结束
        }
        condition.notify_all();//唤醒所有线程
        //带引用符可以修改，不带&为只读
        for (auto &i : threads)
        {
            i.join();
        }
        
       
    }


    template<typename F, typename... Args>
    decltype(auto) //自动返回值类型推导
    enqueue(F&& f, Args&&... args) {
        std::function<void()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        condition.notify_one();
    }
};

int main(){
    threadpool pool(4);
    for(auto i=0;i<10; ++i)
    {
        pool.enqueue([i]{
            std::cout<<" task : "<<i<<" 正在运行"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));//休息一秒
            std::cout<<" task : "<<i<<" 已经结束"<<std::endl;
        });
    }
    
}
