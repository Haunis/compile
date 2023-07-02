gcc和g++区别:
https://www.zhihu.com/question/20940822

-Wl,rpath=作用
https://blog.csdn.net/weixin_34191734/article/details/91871173


g++和gcc的区别:
	g++ = gcc -xc++ -lstdc++ -shared-libgcc
	-xc++: 表示默认语言是c++,gcc默认把.c文件按c语言编译,g++默认把.c文件按cpp编译
	-lstdc++: gcc不会自动添加c++标准库,需要手动指定

	编译:
		gcc区分.c和.cpp文件,.c文件按c程序编译,.cpp的按c++程序编译
		g++不区分.c和.cpp文件,均按c++程序编译
		编译.cpp文件时,g++调用gcc二者等价?
	链接:
		gcc编译.cpp时不能自动和c++程序使用的库连接,所以通常使用g++进行链接


g++常用参数:
	-L./math：链接时-L后跟连接库的路径，‘./math’表示要连接的库所在目录
    -I./math：表示要连接的头文件所在目录
	-ladd: 链接动态库libadd.so
	
	-Wl: 选项告诉编译器将后面的参数传递给链接器
		GCC/G++链接时优先链接动态库，如果没有动态库，则链接相应的静态库。
		同时，GCC/G++也提供了链接选项 -Wl,-Bstatic 和 -Wl,-Bdynamic 供用户指定链接动态库或者静态库。
		-Wl,-Bstatic指示跟在后面的-lxxx选项链接的都是静态库，-Wl,-Bdynamic指示跟在后面的-lxxx选项链接的都是动态库。
		如下:g++ -L. -o main main.cc -Wl,-Bstatic -ltest -Wl,-Bdynamic
		前面的 -Wl,-Bstatic指示链接libtest.a静态库，后面的 -Wl,-Bdynamic指示链接系统动态库
		
	-Wl,--rpath=用于运行时搜索动态库

	-S:只编译,不汇编,不链接,生成.s文件里面是汇编指令,可用cat查看
		如: g++ -S main.cpp

输出带源代码的汇编文件：
	https://www.cnblogs.com/fengkang1008/p/4652193.html
	1.生成.o文件和.s文件
		g++ -g -c hello.cpp
		g++ -S hello.cp
	2.生成含有调试信息，cpp源码的汇编代码
		objdump -S hello.o > dump.s