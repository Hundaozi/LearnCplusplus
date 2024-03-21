cmake_minimum_required(VERSION 3.28.3)
project(Json)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 17)

# 头文件导入
include_directories(${PROJECT_SOURCE_DIR}/include)
# 设置可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 源文件导入
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

add_executable(
    Json 
    ${SRC_LIST}
)