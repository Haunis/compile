cmake_minimum_required(VERSION 3.15)

project(libpower3)#项目信息随便填

#查找当前目录下所有源文件，并将名称保存到DIR_SRC变量
aux_source_directory(. DIR_SRC)

#包含lib目录下的头文件，这样的话main.cpp就不用写完整路径了
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/add")

#因为没执行add_subdirectory(),所以必须要指定静态库目录
link_directories("${PROJECT_SOURCE_DIR}/lib") 



add_subdirectory(add)  #子目录下的CMakeLists.txt也会被处理


#生成可执行文件
add_executable(main ${DIR_SRC})

target_link_libraries(main add power)