#include<stdio.h>
//#include"add.c"  //可以include.c文件
#include"add.h"

extern int a;//不使用extern也可以
int main(){
	int sum = add(7,8);
	printf("7+8 = %d\n",sum);
	printf("a = %d\n",a);
	return 0;
}
