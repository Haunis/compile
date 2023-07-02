和gcc使用类似
一个.c或者.cpp和其include的头文件为一个编译单元

1.编译单个文件成可执行文件
	g++ main.cpp		#默认生成a.out
	g++ -o main main.cpp	#生成main

2.编译单个文件成.o文件
	g++ -c -o main.o main.cpp		#生成main.o

3.编译多个文件成可执行文件
	g++ -o main main.cpp add.cpp

4.将多个.o文件链接成一个可执行文件
	g++ -o main main.o add.o  
	g++ main.o add.o -o main -lm

常用选项:
	c11支持:
	g++ -std=c++11 -o output input

	链接静态库:
	g++ -o output input xxx.a

	链接动态链接库:
	g++ -o output input -lxxx.so

ldd:
	可查看生成可执行目标的依赖
	使用: ldd main

g++ -M main.cpp:
	查看main.cpp所依赖的头文件
	-M 包含标准头文件
	-MM 只包含本工程
