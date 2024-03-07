#include <iostream>
#include <string>
#include "threadpool.h"

void print(int a, double b, const char *c, std::string d){
    std::cout << a << b << c << d << std::endl;
}

void test(){
    std::cout << "hellp" << std::endl;
}

int main(int argc, char const *argv[])
{
    ThreadPool *poll = new ThreadPool();
    std::function<void()> func1 = std::bind(print, 1, 3.14, "hello", std::string("world"));
    std::function<void()> func2 =std::bind(test);
    poll->add(func1);
    poll->add(func2);
    delete poll;
    return 0;
}