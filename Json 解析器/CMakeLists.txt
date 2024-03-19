cmake_minimum_required(VERSION 3.16.2)
project(JsonParser 
        VERSION 1.0 
        LANGUAGES C CXX
        DESCRIPTION "一个普通的JSON解析器")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 指定需要的头文件目录
# 设置头文件变量到项目中
set(headers include/)
include_directories(${headers})
include(CTest)
enable_testing()

set(
    SRC_LIST 
    
  
    src/main.cpp
)
add_executable(JsonParser ${SRC_LIST})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# 输出可执行文件位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include(CPack)
