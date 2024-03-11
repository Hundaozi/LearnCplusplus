#include "include/Buffer.h"
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

void Buffer::Append(const char *str, int size) {
  for (auto i = 0; i < size; ++i) {
    if (str[i] == '\0') {
      break;
    }
    //兼容C其实是无奈之选择
    buf_.push_back(str[i]);
  }
}
//获取buffer的大小
ssize_t Buffer::Size() { return buf_.size(); }
//将buffer转换为C字符串
// buf_是一个std::string
const char *Buffer::ToStr() { return buf_.c_str(); }
//清空缓冲区
void Buffer::Clear() { buf_.clear(); }
//将输入的数据整行导入std::string中
void Buffer::Getline() {
  buf_.clear();
  std::getline(std::cin, buf_);
}
//更新buffer
void Buffer::SetBuf(const char *buf) {
  buf_.clear();
  buf_.append(buf);
}
