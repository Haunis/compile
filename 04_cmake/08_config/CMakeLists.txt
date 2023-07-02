#cmake要求的最低版本
cmake_minimum_required(VERSION 2.8)
project(Fourth_Project)#项目信息，随便指定

set(CMAKE_INCLUDE_CURRENT ON)#这行代码可以不要

#是否使用Power库
option(USE_POWER "use provided math implementation" ON)

#加入配置头文件，用于处理CMake对源码的设置
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  #"${PROJECT_BINARY_DIR}/config.h"#生由config.h.in生成,在build目录下
  "${PROJECT_SOURCE_DIR}/config.h"#由config.h.in生成,在当前目录下
)

#是否加入Power库
if(USE_POWER)
	#把子目录包含进来,在使用子目录的时候,就不用引用全路径
	include_directories("${PROJECT_SOURCE_DIR}/math") 
	add_subdirectory(math) #子目录的CMakeLists也会被编译
#	set (EXTRA_LIB ${EXTRA_LIB} Power)#demo设置的是EXTRA_LIBS
	set (EXTRA_LIB power)#将生成的库指向EXTRA_LIB,不明白两个参数和三个参数的区别
endif(USE_POWER)

# #查找当前目录所有源文件，并保存到DIR_SRC变量里
# aux_source_directory(. DIR_SRC)

#生成可执行目标 main
add_executable(main ${DIR_SRC})

#链接Power库
target_link_libraries(main ${EXTRA_LIB}) #或者power也行
