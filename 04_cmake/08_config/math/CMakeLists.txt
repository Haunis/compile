#查找当前目录所有源文件，并保存到DIR_LIB_SRC
aux_source_directory(. DIR_LIB_SRC)
#根据源文件，生成静态链接库power
add_library(power ${DIR_LIB_SRC})
