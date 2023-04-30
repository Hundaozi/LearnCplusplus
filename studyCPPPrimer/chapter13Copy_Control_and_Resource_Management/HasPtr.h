#ifndef HASPTR_H
#define HASPTR_H
#include<iostream>

class HasPtr{

    public:

        HasPtr(const std::string &s = std::string()):
            ps(new std::string(s)), i(0) , use(new std::size_t(1)){}

        HasPtr(const HasPtr &p):
            ps(new std::string(*p.ps)), i(p.i) , use(p.use) { ++*use; }

        HasPtr& operator=(const HasPtr&);

        ~HasPtr(){ delete ps; }       //析构函数
    
    private:
        std::string *ps;
        int i;

        std::size_t *use;   //保留有多少对象分享了 *ps 的成员
};





#endif

