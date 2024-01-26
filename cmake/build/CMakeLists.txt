cmake_minimum_required(VERSION 3.0)
project(CALC)
set(SRC_LIST add.c  div.c   main.c  mult.c  sub.c)
add_executable(app  ${SRC_LIST})

#增加-std=c++17
set(CMAKE_CXX_STANDARD 17)

#设置输出路径 linux下获取当前路径为 pwd
set(HOME /home/hundaozi/github/LearnCplusplus/cmake/app_out)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)



