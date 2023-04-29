#ifndef STRBLOB_H
#define STRBLOB_H
#include<vector>
#include<memory>
#include<string>
#include"StrBlob.h"
#include<stdexcept>
class StrBlob;
class StrBlobPtr{
    public:

        StrBlobPtr(): curr(0){}    //默认构造函数
        
        StrBlobPtr(StrBlob &a, size_t sz=0):wptr(a.data), curr() {} //第二个构造函数

        std::string& deref() const;       //间接引用
        StrBlobPtr& incr();               //增加

    private:

        std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string &) const;

        std::weak_ptr<std::vector<std::string>> wptr;   //弱智能指针，类型为 存储着string类型的vector

        std::size_t curr;       //array中的当前位置

    std::shared_ptr<std::vector<std::string>>
    StrBlobPtr::check(std::size_t i, const std::string &msg) const
    {
        auto ret=wptr.lock();
        if(!ret)
            throw std::runtime_error("unbound StrBlobPtr");
        if(i>= ret->size())
            throw std::out_of_range(msg);
        return ret;
    }

    //间接引用
    std::string& StrBlobPtr::deref() const
    {
        auto p= check(curr, "dereference past end");
        return (*p)[curr];
    }

    //位置增加
    StrBlobPtr& StrBlobPtr::incr()
    {
        check(curr, "increment past end of StrBlobPtr");
        ++curr;
        return *this;
    }

};










#endif