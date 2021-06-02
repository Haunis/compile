/**
 * 编译：g++ -o hello main.cpp add.cpp
 * 
 * main入口函数参数说明
 * 执行：./main  aaa 
 * argc = 2 --一共有两个参数,表示shell程序接受的参数个数？？？？
 * argv[0]=./main; 但如果是绝对路径执行如/home/xxx/Desktop/main aaa,则该参数就是绝对路经下的字符串
 * argv[1]=aaa
 */
#include <iostream>
#include "add.h"
#include "add.h"

using namespace std;

int main(int argc, char *argv[])
{
	int result = add(3, 4);
	cout << "3+4=" << result << endl;

	cout << "argv[0]=" << argv[0] << endl;
	printf("argc = %d\n", argc);
	if (argc > 1)
	{
		printf("argv[1]=%s\n", argv[1]);
	}
	return 0;
}
