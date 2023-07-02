cmake_minimum_required(VERSION 2.8)
project(Second_Project)#项目信息随便填

#查找当前目录下所有源文件，并将名称保存到DIR_SRC变量
aux_source_directory(. DIR_SRC)
# MESSAGE(FATAL_ERROR "just test|||||||")
MESSAGE(STATUS "DIR_SRC:${DIR_SRC}")

#添加math子目录:math目录下的CMakeLists.txt和源码也会被处理
add_subdirectory(math)
#包含math子目录下的头文件:这样的话main.cpp就不用写完整路径了
include_directories("${PROJECT_SOURCE_DIR}/math")
#添加需要链接的库的目录:如果使用的动态库的话,可以不用添加动态库的目录
#因为执行了add_subdirectory()所以link_directories可以不用指定
#link_directories("${PROJECT_SOURCE_DIR}/lib")  


#添加链接库方式1:link_libraries
#link_libraries要在add_executable之前
link_libraries(power)

#生成可执行文件
add_executable(main ${DIR_SRC})

#添加链接库方式2:target_link_libraries
#如果执行了add_subdirectory,子目录的CMakeLists.txt处理后,链接时会自动到
#build/math/下寻找libpower.a库
#target_link_libraries(main power)

#或者给库设置别名
#set(slib power)#将slib指向power
#target_link_libraries(main ${slib})




