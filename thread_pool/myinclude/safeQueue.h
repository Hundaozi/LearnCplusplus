//只编译一次
#pragma once

//锁库
#include <mutex>
//队列库
#include <queue>


template <typename T>
class safeQueue{
    private:
        //声明一个队列
        std::queue<T> my_queue;
        //声明一个锁
        std::mutex my_mutex;

    public:
        //构造
        safeQueue(){}

        safeQueue(safeQueue& other){}

        //析构
        ~SafeQueue() {}

        //判断任务队列是否为空
        bool empty(){
            std::unique_lock<std:mutex> lock(my_mutex);
            return my_queue.empty();
        }

        //获取队列里任务的个数
        int size(){
            std::unique_lock<std::mutex> lock(my_mutex);
            return my_queue.size();
        }

        //将任务加入队列
        void enqueue(T& t){
            std::unique_lock<std::mutex> lock(my_mutex);
            my_queue.push(t);
        }

        //判断任务是否出队了
        bool dequeue(T& t){
            std::unique_lock<std::mutex> lock(my_mutex);

            //
            if (my_queue.empty()){

                return false;
            }

            //front 返回队列里第一项的引用
            //将其转换为右值
            t =std::move(my_queue.front());

            //弹出任务
            my_queue.pop();

            return true;
        }

};
