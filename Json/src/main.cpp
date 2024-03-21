#include "hello.h"
void Hello::say_hello(){
    std::cout<<"hello world! \n";
}
int main()
{
    Hello my_hello;
    my_hello.say_hello();
    return 0;
}