#查找当前目录下所有源文件，并保存到DIR_LIB_SRC变量
aux_source_directory(. DIR_LIB_SRC)



MESSAGE(STATUS "PROJECT_SOURCE_DIR----->:" ${PROJECT_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/include")
#因为没执行add_subdirectory(),所以必须要指定静态库目录
link_directories("${PROJECT_SOURCE_DIR}/lib") 


#编译成静态链接库,生成的静态链接库在build/add/libadd.a
#第一个参数：生成库名
#第二个参数: STATIC--静态库;SHARED--动态库;OBJECT--.o文件; 不写的话,默认是静态库
#第三个参数：所需的源文件
add_library(add STATIC ${DIR_LIB_SRC})


target_link_libraries(add power)

