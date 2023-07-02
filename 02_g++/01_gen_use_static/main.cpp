#include<stdio.h>
#include<stdlib.h>
#include"math/add.h"
//#include"add.h" //g++编译会报错,找不到头文件

int main(){
	int x = 3,y= 4;
	int result = add(x,y);
	printf("%d + %d = %d\n",x,y,result);
	return 0;
}
