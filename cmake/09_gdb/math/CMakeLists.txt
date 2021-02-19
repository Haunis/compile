#查找当前目录所有源文件,并保存到DIR_LIB_SRC
aux_source_directory(. DIR_LIB_SRC)
#生成静态库,生成../build/math/libPower.a
add_library(Power ${DIR_LIB_SRC})

install(TARGETS Power DESTINATION bin)
install(FILES power.h DESTINATION include)
