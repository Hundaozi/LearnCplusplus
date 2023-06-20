#include<iostream>
#include<thread>

void hello()
{
    std::cout<<"Hello Conncurrent World \n";
}

int main()
{
    std::thread mythread(hello);
    mythread.join();
}