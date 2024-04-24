cmake_minimum_required(VERSION 3.28.3)
project(Designpattern VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

add_executable(Designpattern 观察者模式.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
