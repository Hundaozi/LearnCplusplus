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

    HasPtr::~HasPtr()
    {
        if(--*use==0){            //如果引用计数为0
            delete ps;            //释放掉 ps和use
            delete use;
        }
    }

    HasPtr& HasPtr::operator=(const HasPtr &rhs)
    {
        --*rhs.use;      //increment the use count of the right-hand operand
        if(--*use == 0){
            delete ps;
            delete use;
        }
        //重载操作
        ps=rhs.ps; 
        i=rhs.i;
        use=rhs.use;
        return *this;
            
    }
};





#endif

