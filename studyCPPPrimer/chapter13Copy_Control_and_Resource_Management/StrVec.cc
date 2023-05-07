#include "StrVec.h"

#include <string>
#include <utility>

int main(){

    StrVec vec;   //空的向量

    std::string s= "some string or another";

    vec.push_back(s);    //call push_back(const string&) 左值
    vec.push_back("done"); //call push_back(std::string &&)

    return 0;
}