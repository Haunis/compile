#要求的最低版本
cmake_minimum_required (VERSION 2.8)

#项目信息
project(demo7)
set(Demo_VERSION_MAJOR 1)
set(Demo_VERSION_MINOR 0)

#设置工程包含当前目录(build下的头文件会被包含)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


MESSAGE(STATUS "CMAKE_ROOT:${CMAKE_ROOT}")
MESSAGE(STATUS "EXTRA_LIB: ${EXTRA_LIB}")
MESSAGE(STATUS "CMAKE_INCLUE_CURRENT_DIR:"${CMAKE_INCLUDE_CURRENT_DIR})

#检查系统是否支持pow函数
#检测不到...
include (${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists(pow HAVE_POW)

#加入配置文件,生成config.h文件
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"	
	"${PROJECT_BINARY_DIR}/config.h" #config.h会生成在build下
	#"${PROJECT_SOURCE_DIR}/config.h"
)

#是否加入power库
if(NOT HAVE_POW)
	MESSAGE(STATUS "系统不包含pow函数")
	#包含math目录下的头文件，这样的话main.cpp就不用写完整路径了
	include_directories ("${PROJECT_SOURCE_DIR}/math")

	#math目录下的CMakeLists.txt也会被处理
	add_subdirectory(math)
	set(EXTRA_LIB ${EXTRA_LIB} Power)
	#set(EXTRA_LIB Power) #EXTRA_LIB指向math生成的power库
else()
	MESSAGE(STATUS "系统包含pow函数")
endif(NOT HAVE_POW)

#查找当前目录下所有源文件,并将文件名保存到DIR_SRC变量
aux_source_directory(. DIR_SRC)
#生成可执行文件
add_executable(main ${DIR_SRC})

#链接power库
target_link_libraries(main ${EXTRA_LIB})

install (TARGETS main DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)

#启用测试
enable_testing()	
#测试是否正常运行
add_test(test_run main 5 2)

#帮助信息是否可以正常显示
add_test(test_usage main)
set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "argv*")

#测试5的平方
add_test(test_5_2 main 5 2)
set_tests_properties(test_5_2 PROPERTIES PASS_REGULAR_EXPRESSION "= 25")

#定义一个宏
macro(do_test arg1 arg2 result)
	add_test(test_${arg1}_${arg2} main ${arg1} ${arg2})
	set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_RREGULAR_EXPRESSION ${result})
endmacro(do_test)

do_test(3 2 "= 9")
do_test(3 3 "= 27")


#构建一个 CPack 安装包
#导入InstallRequiredSystemLibraries,以便之后导入CPack模块
include (InstallRequiredSystemLibraries) 
#设置版权信息和版本信息等
set (CPACK_RESOURCE_FILE_LICENSE"${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
include (CPack) #导入CPack

