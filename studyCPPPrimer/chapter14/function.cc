#include<iostream>
#include<functional>

int add(int i, int j){

    return i+j;
}

auto mod=[](int i ,int j){return i%j;};

struct divide{
    int operator()(int denominator, int divisor ){
        return denominator /divisor;
    }
};
int main(){

    std::function<int(int, int)> f1=add;              //函数指针
    std::function<int(int, int)> f2=divide();      

    std::function<int(int, int)> f3=[](int i, int j){ return i * j;};

    std::cout<<f1(4, 2)<<std::endl;     //输出6

    std::cout<<f2(4, 2)<<std::endl;     //输出2

    std::cout<<f3(4, 2)<<std::endl;     //输出8
}


