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
int main(){

    std::vector<unsigned> v1(bad_randVec());
    std::vector<unsigned> v2(bad_randVec());

    std::cout<<((v1==v2)? "equal " : " not equal ") <<std::endl;

    std::vector<unsigned> v3(good_randVec());
    std::vector<unsigned> v4(good_randVec());

    std::cout<<((v3==v4)? "equal " : " not equal ") <<std::endl;
    return 0;
}