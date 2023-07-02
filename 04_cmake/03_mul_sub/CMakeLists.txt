#CMake要求最低版本号,VERSION和后面的数字要分开
cmake_minimum_required(VERSION 2.8)

project(Second_Project)#项目信息，可以随便指定
aux_source_directory(. DIR_SRC) #遍历目录，将遍历到的源文件保存到.DIR_SRC变量

#add_subdirectory(math) #子目录下的CMakeLists.txt也会被处理
#include_directories("${PROJECT_SOURCE_DIR}/math")#包含子目录，这样main.cpp就不用include完整路径

add_library(hhh OBJECT power.cpp)
#add_library(power STATIC power.cpp)

#add_library(my_static_lib static $<TARGET_OBJECTS:hhh> power.cpp)

#第一个参数是生成的目标文件，后面的参数是要编译的源文件
add_executable(main $<TARGET_OBJECTS:hhh> main.cpp)
# add_executable(main ${DIR_SRC})
# add_executable(main ${DIR_SRC} $<TARGET_OBJECTS:power>)
# add_library(my_static_lib STATIC power.cpp $<TARGET_OBJECTS:power>)

