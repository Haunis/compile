#cmake 要求的最低版本好，VERSION要大写
cmake_minimum_required(VERSION 2.8)

project(First_Project)#项目信息，随笔写

#生成可执行文件；第一个参数是生成的目标文件，第二个参数是源文件
add_executable(main main.cpp)

MESSAGE(STATUS "QNX_HOST: $ENV{QNX_HOST}")
MESSAGE(STATUS "QNX_TARGET: $ENV{QNX_TARGET}")
MESSAGE(STATUS "CMAKE_ROOT: ${CMAKE_ROOT}")
