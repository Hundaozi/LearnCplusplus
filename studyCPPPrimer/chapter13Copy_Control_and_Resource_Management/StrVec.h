#ifndef STRVEC_H
#define STRVEC_H

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

class StrVec{

    public:

        StrVec():
            elements(nullptr), first_free(nullptr), cap(nullptr){} //初始化空指针
        StrVec(const StrVec&);             //复制构造函数
        StrVec &operator=(const StrVec&);   //复制分配函数
        ~StrVec(); //析构函数

        void push_back(const std::string &);  //复制项
        void push_back(std::string&&);    //通过右值引用

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

        std::string *first_free;  //特制 指向数组中第一个项的指针

        std::string *cap;      //指向数组末尾后面的一个指针
    

};


inline
//alloc是静态数据成员，类内只是对静态成员进行了声明而不是定义，如果没有在类外进行定义的话就会出现未定义的引用。
std::allocator<std::string> StrVec::alloc;


//释放函数
inline
void StrVec::free()
{
    if(elements){

        for( auto p=first_free; p!=elements; ) 
            alloc.destroy(--p);                 //销毁数组中的项
            alloc.deallocate(elements, cap-elements);   //解除分配,释放内存
    }
}

inline
void StrVec::push_back(const std::string &s)
    {
        chk_n_alloc();
        //为了使用原始的内存，我们必须调用 construct，which will construct an object in that memory
        alloc.construct(first_free++, s); //第二个参数是要去到的位置
    }

inline
void StrVec::push_back(std::string &&s)
    {   
        chk_n_alloc();                  //重新分配strvec 如果必须得的话

        alloc.construct(first_free++, std::move(s));
    }

inline
std::pair<std::string*, std::string *>
    StrVec::alloc_n_copy(const std::string*b, const std::string*e)
    {
        auto data=alloc.allocate(e -b);

        return { data, uninitialized_copy( b ,e , data)};
    }

//当我们复制或者分配一个StrVec时候我们使用这个分配复制函数

    
inline
StrVec::StrVec(const StrVec&s)
{
    auto newdata= alloc_n_copy(s.begin(), s.end()); //alloc_n_copy是一个pair
    elements=newdata.first;
    first_free=cap=newdata.second;
}
inline
StrVec::~StrVec(){ free();}    //析构函数，调用释放函数

inline
StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data=alloc_n_copy(rhs.begin(),rhs.end());

    free();
    elements=data.first;
    first_free=cap=data.second;
    return *this;         //返回到当前函数
}

    //再分配函数
inline
void StrVec::reallocate()
{   
    //分配空间两次 作为许多项当前的大小
    auto newcapacity= size() ? 2 * size() :1;
    //分配新的内存
    auto newdata =alloc.allocate(newcapacity);


    auto dest=newdata;       //在新数组中指向下一个释放的位置
    auto elem =elements;     //elem是在老数组中指向一个项
        
    for(size_t i=0; i != size();++i)
        alloc.construct(dest++, std::move(*elem++));

    free();             //释放空间
    elements=newdata;   //新数据给项

    first_free=dest;    

    cap=elements+newcapacity;  //新的容量为项数+新容量部分

        
}


#endif