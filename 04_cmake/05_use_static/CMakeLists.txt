cmake_minimum_required(VERSION 2.8)

project(Second_Project)#项目信息随便填

#查找当前目录下所有源文件，并将名称保存到DIR_SRC变量
aux_source_directory(. DIR_SRC)


###添加lib子目录,lib目录下的CMakeLists.txt和源码也会被处理
#add_subdirectory(lib)
#包含lib目录下的头文件，这样的话main.cpp就不用写完整路径了
include_directories("${PROJECT_SOURCE_DIR}/lib")
#添加需要链接的库的目录;如果使用的动态库的话,可以不用添加动态库的目录
#因为没执行add_subdirectory(),所以必须要指定静态库目录
#add_subdirectory()--执行子目录CMakeLists.txt
link_directories("${PROJECT_SOURCE_DIR}/lib")  


#使用link_libraries或target_link_libraries均可
#link_libraries要在add_executable之前
link_libraries(power)
#生成可执行文件
add_executable(main ${DIR_SRC})

#添加链接库；
#set(slib power)#将slib指向power
#target_link_libraries(main ${slib})  
#target_link_libraries(main libpower.a)#ok
#target_link_libraries(main power)#ok


