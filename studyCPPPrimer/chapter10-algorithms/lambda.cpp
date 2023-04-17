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
int main(){

    fun1();

    return 0;
}