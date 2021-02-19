/*
 参考AndroidRuntime.cpp的写法;
 如果传入的是个函数，如REG_JNI(fun),则返回{arg1 (*fun)(arg2*)}
*/

#include <stdio.h>
#define REG_JNI(name)	{ name } //返回一个结构体

struct RegJNIRe
{
	int (*mProc)(int*); //函数指针;函数名-mProc,参数-int*,返回值-int
};
int fun(int *p)
{
	printf("fun called :%d\n", *p);
	return -1;
}

int main(int arg,char*argv[]){
	int temp = 100;

	RegJNIRe reg_struct = REG_JNI(fun);//调用宏得到一个结构体
	reg_struct.mProc(&temp);
}
