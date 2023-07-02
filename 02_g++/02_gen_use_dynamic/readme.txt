参考：https://www.linuxidc.com/Linux/2013-11/93010.htm
-fPIC:https://www.cnblogs.com/cswuyg/p/3830703.html

一、编译生成so动态库
	编译math目录的add.cpp生成libadd.so动态库
	g++ add.cpp -fPIC -shared -o libadd.so
	-fPIC:使用地址无关代码 Position Independent Code
	linux上编译要使用 -fPIC参数

二、链接使用libadd.so
	g++ -o main main.cpp -ladd  或者使用下述编译
	g++ main.cpp -ladd -o main
	-ladd：编译器查找动态链接库时有隐含的命名规则--即在给出的名字前面加上lib，名字后面加上.so，即libadd.so
	链接时候会自动到/lib或者/usr/lib找add.so,所以应该将生成的动态链接库libadd.so拷贝至/lib或者/usr/lib

	补充：使用带其他参数的编译方式
	g++ main.cpp -L./math -I./math -ladd -o main
	-L./math：-L后跟连接库的路径，‘./math’表示要连接的库所在目录
    -I./math：表示要连接的头文件所在目录
	-ladd: 链接动态库libadd.so

	g++ -o main -L./math -I./math main.cpp -ladd   //ok
	g++ -o main -L./math -I./math -ladd main.cpp   //不行

	编译时指定运行时搜索的依赖库路径： -Wl,-rpath=./math， 表示运行时到./math路径下搜索libadd.so
	g++ -o main -L./math -I./math main.cpp -Wl,-rpath=./math -ladd
	
三、查看可执行文件的动态库依赖关系
	ldd test
