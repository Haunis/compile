cmake_minimum_required(VERSION 2.8)
project(Fifth_Porject)#项目信息随便指定

#设置工程包含当前目录(会包含build/config.h)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#是否使用Power库
option(USE_POWER "use provided math implemention" ON)
#建立config.h.in配置文件，并生成config.h文件;根据USE_POWER决定生成的config.h
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"#config.h会生成在build下
	#"${PROJECT_SOURCE_DIR}/config.h"#在当前目录生成config.h文件
)

if(USE_POWER)
	#包含math目录下的头文件，这样的话main.cpp就不用写完整路径了
	include_directories("${PROJECT_SOURCE_DIR}/math")
	add_subdirectory(math)#math目录下的CMakeLists.txt也会被处理
#	set (EXTRA_LIB ${EXTRA_LIB} Power)#demo设置的是EXTRA_LIBS
	set (EXTRA_LIB Power)#将生成的库指向EXTRA_LIB,不明白两个参数和三个参数的区别
endif(USE_POWER)

#查找当前目录下所有源文件，并将文件名保存到DIR_SRC变量
aux_source_directory(. DIR_SRC)
#生成可执行目标main
add_executable(main ${DIR_SRC})

#链接Power库
target_link_libraries(main ${EXTRA_LIB})
#target_link_libraries(main Power)#编译不过


install(TARGETS main DESTINATION bin)#执行sudo make install 之后可执行文件main被拷贝到/usr/bin下
install(FILES config.h DESTINATION include)#执行 sodu make install之后，config.h被拷贝到/usr/bin/include 


enable_testing()#启用测试
add_test(test_run main 5 2)#测试程序是否成功运行

add_test(test_usage main)#测试帮助信息是否正常显示
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "argv*")

add_test (test_5_2 main 5 2)#测试5的平方
set_tests_properties(test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "= 25")#注意和main.cpp中最后打印的格式要一致

add_test (test_5_3 main 5 3)
set_tests_properties(test_5_3 PROPERTIES PASS_REGULAR_EXPRESSION "= 125")

#一个一个写太麻烦，可以定义一个宏来简化测试
macro(do_test arg1 arg2 result)
	add_test(test_${arg1}_${arg2} main ${arg1} ${arg2})
	set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

do_test(2 2 "= 4") 
do_test(2 3 "= 8") 
do_test(2 4 "= 16") 

#支持gdb调试
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
