#如果源文件太多，一个一个写太麻烦，可使用函数遍历相应目录，并将遍历到的源文件保存到.DIR_SRC变量
aux_source_directory(. DIR_SRC)

add_library(power.o OBJECT ${DIR_SRC})
