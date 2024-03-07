#include "Buffer.h"
#include <string.h>
#include <iostream>
Buffer::Buffer()
{
}

Buffer::~Buffer()
{
}

void Buffer::append(const char* _str, int _size){
    for(auto i = 0;i< _size; ++i){
        if(_str[i]== '\0') break;
        //Appends character c to the end of the string, increasing its length by one.
        buf.push_back(_str[i]);//将字符串一个个往里面灌

    }
}

ssize_t Buffer::size(){
    return buf.size();
}

const char* Buffer::c_str(){
    return buf.c_str();
}

void Buffer::clear(){
    buf.clear();
}

void Buffer::getline(){
    buf.clear();
    std::getline(std::cin,buf);
}