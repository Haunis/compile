
子目录CMakeLists不引入静态库的情况下使用静态库

在主目录CMakeLists.txt中链接libpower.a,并include libpower.a的头文件
此时add/CMakeLists.txt中不链接libpower.a，但add.cpp可以使用libpower.a


main.cpp可以使用libadd.a 和libpower.a






