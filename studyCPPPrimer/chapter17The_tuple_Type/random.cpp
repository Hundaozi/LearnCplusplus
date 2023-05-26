#include<iostream>
#include<random>
#include<vector>

std::vector<unsigned> bad_randVec()
{
    std::default_random_engine e;
    std::uniform_int_distribution<unsigned> u(0,9);

    std::vector<unsigned> ret;
    for(size_t i=0; i<100;++i)
        ret.push_back(u(e));
    return ret;
}

std::vector<unsigned> good_randVec()
{
    static std::default_random_engine e;
    static std::uniform_int_distribution<unsigned> u(0,9);
    std::vector<unsigned> ret;
    for(size_t i=0;i<100;++i)
        ret.push_back(u(e));
    return ret;
}

void func()
{
    std::default_random_engine e1;
    std::default_random_engine e2(2147483646);

    std::default_random_engine e3;

    e3.seed(32767);

    std::default_random_engine e4(32767);

    for(size_t i=0;i!=100;++i){
        if(e1()==e2())
            std::cout<<" unseeded match at iteration: "<< i <<std::endl;
        if(e3()!= e4())
            std::cout<<" seeded differs at oteration: "<< i <<std::endl;
    }
}
int main(){

    // std::vector<unsigned> v1(bad_randVec());
    // std::vector<unsigned> v2(bad_randVec());

    // std::cout<<((v1==v2)? "equal " : " not equal ") <<std::endl;

    // std::vector<unsigned> v3(good_randVec());
    // std::vector<unsigned> v4(good_randVec());

    // std::cout<<((v3==v4)? "equal " : " not equal ") <<std::endl;
    func();
    return 0;
}