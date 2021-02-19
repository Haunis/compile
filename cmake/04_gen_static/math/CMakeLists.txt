#查找当前目录下所有源文件，并保存到DIR_LIB_SRC变量
aux_source_directory(. DIR_LIB_SRC)

#编译成动态链接库,生成的动态链接库在build/math/libpower.a
#第一个参数：生成库名
#第二个参数: STATIC--静态库;SHARED--动态库;OBJECT--.o文件; 不写的话,默认是静态库
#第三个参数：所需的源文件
add_library(power STATIC ${DIR_LIB_SRC})

