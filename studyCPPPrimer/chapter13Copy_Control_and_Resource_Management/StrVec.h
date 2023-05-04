#ifndef STRVEC_H
#define STRVEC_H

#include <iostream>
#include <memory>
#include <utility>


class StrVec{

    public:

        StrVec():
            elements(nullptr), first_free(nullptr), cap(nullptr){} //初始化空指针
        StrVec(const StrVec&);             //复制构造函数
        StrVec &operator=(const StrVec&);   //复制分配函数
        ~StrVec(); //析构函数

        void push_back(const std::string &);  //复制项

        size_t size() const{ return first_free - elements;} //大小

        size_t capacity() const{ return cap- elements; }   

        std::string *begin() const{ return elements; }

        std::string *end() const { return first_free;}



    private:


        static std::allocator<std::string> alloc;  //分配器

        void chk_n_alloc(){ if(size()==capacity()) reallocate(); } //检查扩容函数

        std::pair<std::string*, std::string*> alloc_n_copy(const std::string *, const std::string*);

        void free();        //销毁项和释放空间

        void reallocate();  //获取更多空间，复制存在的项

        std::string *elements;  //指向数组中第一个项的指针

        std::string *first_free;  //指向数组中第一个项的指针

        std::string *cap;      //指向数组末尾后面的一个指针

};














#endif