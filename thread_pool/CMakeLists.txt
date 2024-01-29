#设置cmake版本
cmake_minimum_required (VERSION 3.2)

#文件名
project (thread_pool)

#编译器选项，设置版本
add_compile_options(
    -std=c++14
    -D_DEBUG
    -g
)


include_directories (
	myinclude/
)

set(HEADERS myinclude/safeQueue.h myinclude/thread_pool.h)
 
set(SOURCES mycpp/main.cpp)

SET(CMAKE_CXX_FLAGS -pthread)

# main.cpp
add_executable(main ${HEADERS} ${SOURCES})
target_link_libraries(main)
