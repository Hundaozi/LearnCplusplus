#pragma once
#include <string>

class Buffer{
    private:
        std::string buf;
    public:
        Buffer();
        ~Buffer();
        void append(const char* _str, int _size);
        ssize_t size();
        const char* c_str();//与C字符串的对接
        void clear(); //清空缓冲
        void  getline();//获取输入
        void setBuf(const char*);
};