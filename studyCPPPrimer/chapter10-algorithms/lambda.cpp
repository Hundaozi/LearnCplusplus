#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

void fun1()
{
    size_t v1=42;
    auto f=[v1]{return v1; }; //当lambda表达式被创建时，捕获的值就被复制了

    v1=0;
    auto j=f();  //j会是42，因为f函数储存了V1的复制值
}

void fun2()
{
    size_t v1=42;
    
    auto f2=[&v1] { return v1; };

    v1=0;

    auto j=f2();      //j的值会是0   ，f2只是引用了v1，f2并不存储v1
}

int main(){

    // fun1();

    fun2();

    return 0;
}