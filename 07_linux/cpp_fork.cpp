/**
 *	fork()参考:https://www.cnblogs.com/ittinybird/p/4492098.html
 *
 * 	wait()参考:https://www.cnblogs.com/black-mamba/p/6886434.html
 *
 *	fork()后产生一个子进程, fork()返回两次值;0-子进程;非0主进程
 *	fork()子进程只进行fork后面的语句,复制前面的父进程的数据，但不执行语句
 *
 *
 *	wait()函数:
 *		如果所有子进程都在进行,则主进程阻塞
 *		所有子进程中只要有一个子进程终止,则主进程不再阻塞
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
void test1();
void test2();
int main()
{
	test1();
//	test2();
	wait(NULL);
	wait(NULL); //sys/wait.h
	return 0;
}

void test1()
{
	printf("main  getpid=%d\n", getpid()); //unistd.h 中的函数

	//调用该方法后,主进程继续向下执行;
	//主进程得到的ret是子进程的pid,子进程得到的ret是0
	//子进程复制父进程的资源,但不执行fork之前的代码,只会继续执行fork之后的代码
	int ret = fork(); 
	if (ret > 0) //非0--主进程
	{
		printf("main  getpid=%d, ret=%d\n", getpid(), ret);
	} else //0 -- 子进程
	{
		printf("zi  getpid=%d, ret=%d\n", getpid(), ret);
	}
}
void test2()
{
	printf("main  getpid=%d\n", getpid()); //unistd.h 中的函数
	for (int i = 0; i < 2; i++)
	{
		printf("before getpid=%d\n", getpid());
		fork();

		//该行代码执行六次;
		//主进程第一次执行后执行2次,并fork出子进程f1;
		//主进程第二次执行后执行2次,并fork出子进程f2;
		//f1会继续执行fork,执行后该行代码又会执行两次
		printf("=======> after getpid=%d\n", getpid());
	}

}
