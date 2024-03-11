#pragma once
#include "Macros.h"
#include <string>

class Buffer {
public:
  Buffer() = default;
  ~Buffer() = default;

  DISALLOW_COPY_AND_MOVE(Buffer);

  //在缓冲区添加数据
  void Append(const char *_str, int _size);
  //设置缓冲区大小
  ssize_t Size();
  //缓冲区字符转换
  const char *ToStr();
  //清空缓冲区
  void Clear();
  //获取输入
  void Getline();
  //设置缓冲区
  void SetBuf(const char *buf);

private:
  //存储缓冲
  std::string buf_;
};