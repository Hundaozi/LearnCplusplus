cmake_minimum_required(VERSION 3.28.3)
project(Json VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB SRC_FILES
    "{PROJECT_SOURCE_DIR}/include/*.h"
    "{PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${CMAKEZ_PROJECT_NAME} ${SRC_FILES})

#指定编译器
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
