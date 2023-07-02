1.生成支持gdb的可执行文件
	g++ -g -o main main.cpp
2.启动调试: gdb main

3.查看代码:list 或者list 1

4.打断点: break 17 (在第17行打断点)

5.查看断点: info break 或者i b

6.设置启动参数: set args 11 12 (如果main(int argv,char*args[])需要参数的话)

7.运行:run

8.step over: next 或者n

9.step into: step 或者s

结束:q
