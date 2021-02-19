#查找当前目录下所有源文件，并保存到DIR_LIB_SRC变量
aux_source_directory(. DIR_LIB_SRC)

#编译成动态链接库,生成的动态链接库在build/math/libmy_power.so
#第一个参数：生成库名，	第三个参数：所需的源文件
add_library(my_power SHARED ${DIR_LIB_SRC})
#创建动态库别名,允许使用别名来链接库
add_library(my::power ALIAS my_power)
