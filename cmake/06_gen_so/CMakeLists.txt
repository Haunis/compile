cmake_minimum_required(VERSION 2.8)

project(Second_Project)#项目信息随便填

#查找当前目录下所有源文件，并将名称保存到DIR_SRC变量
aux_source_directory(. DIR_SRC)

###添加math子目录,math目录下的CMakeLists.txt和源码也会被处理
add_subdirectory(math)

###包含math目录下的头文件，这样的话main.cpp就不用写完整路径了
include_directories("${PROJECT_SOURCE_DIR}/math")

#生成可执行文件
add_executable(main ${DIR_SRC})

#添加链接库；子目录生成的静态链接库在build/math目录下
#set(slib power)#将slib指向power
#target_link_libraries(main ${slib})

###或者使用下面这个也行
#target_link_libraries(main my_power)
#使用my_power的别名
target_link_libraries(main my::power)



