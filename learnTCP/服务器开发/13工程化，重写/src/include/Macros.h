//对MACOS的特殊设置
//
#pragma once
#define LO_LINUX

//禁止拷贝和复制操作
#define DISALLOW_COPY(cname)                                                   \
  cname(const cname &) = delete;            /* NOLINT */                       \
  cname &operator=(const cname &) = delete; /* NOLINT */
//不允许移动与移动赋值
#define DISALLOW_MOVE(cname)                                                   \
  cname(cname &&) = delete;            /* NOLINT */                            \
  cname &operator=(cname &&) = delete; /* NOLINT */
//都不允许
#define DISALLOW_COPY_AND_MOVE(cname)                                          \
  DISALLOW_COPY(cname);                                                        \
  DISALLOW_MOVE(cname);