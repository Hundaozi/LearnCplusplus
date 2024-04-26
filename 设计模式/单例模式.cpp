#include<iostream>


// 最简洁：不需要额外定义类的静态成员
// 线程安全，不需要额外加锁
// 没有烦人的指针
class Singleton {
   public:
    static Singleton& getInstance() {
        static Singleton inst;
        return inst;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

   private:
    Singleton() = default;
};


int main(){
    std::cout<<Singleton::getInstance()<<'\n';
}