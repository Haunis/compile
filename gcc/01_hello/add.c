//头文件的实现文件，可以不include头文件
#include<stdio.h>
#include "add.h"

int a = 23;
int add(int x ,int y){
	int z= multi(x,y);
	printf("%d *%d = %d\n",x,y,z);
	return (x+y);
}


int multi(int x,int y){
	return (x*y);
}
