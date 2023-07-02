#CMake要求最低版本号,VERSION和后面的数字要分开
cmake_minimum_required(VERSION 2.8)

project(Second_Project)#项目信息，可以随便指定

#第一个参数是生成的目标文件，后面的参数是要编译的源文件
#add_executable(main main.cpp power.cpp)

#如果源文件太多，一个一个写太麻烦，可使用函数遍历相应目录，并将遍历到的源文件保存到.DIR_SRC变量
aux_source_directory(. DIR_SRC)
add_executable(main ${DIR_SRC})
