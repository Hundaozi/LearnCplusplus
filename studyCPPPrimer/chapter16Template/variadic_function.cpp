#include<iostream>

template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);

std::string debug_rep(const std::string &);
std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}


template<typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    return os<<t;
}

template<typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args&... rest)
{
    os<<t<<", ";
    return print(os,rest...);
} 


template <typename... Args>
std::ostream &errorMsg(std::ostream &os, const Args&... rest)
{
    return print(os, debug_rep(rest)...);
}
int main()
{   
    int i=0;
    double d=3.14;
    std::string s ="我可真牛逼";
    std::cout<<"世界你好!";
    print(std::cout, i, s, 42);

}