#include<iostream>
#include<random>

int main(){
    std::default_random_engine e;

    for(size_t i=0; i <10; ++i)
        std::cout<<e()<<std::endl;
    return 0;
}