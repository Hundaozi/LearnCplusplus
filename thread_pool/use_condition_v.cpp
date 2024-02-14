#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<queue>

//生产者消费者模型

std::mutex m_mutex;//互斥锁
std::condition_variable m_condition_v; //条件变量
std::queue<int> task_queue;//任务队列

//生产者
void Producer()
{
    for(auto i=0;i<10; ++i)
    {
        std::unique_lock<std::mutex> lock(m_mutex);//加锁
        task_queue.push(i);//增加新任务
        std::cout<<" 生产者, 已添加新任务 : " <<i<<std::endl;

    }
    m_condition_v.notify_one();//唤醒
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

//消费者
void Consumer()
{
    while (1)
    {
        /* code */
        std::unique_lock<std::mutex> lock(m_mutex);//加锁
        m_condition_v.wait(lock, [](){
            return !task_queue.empty();    //如果任务队列不空，则唤醒
        }); //等待
        auto task_value=task_queue.front();
        task_queue.pop();
        std::cout<<" 消费者，已消费任务的编号为： "<<task_value<<std::endl;
    }
    
}
int main()
{
    std::thread producer_thread(Producer);
    std::thread consumer_thread(Consumer);
    producer_thread.join();
    consumer_thread.join();

    return 0;
}