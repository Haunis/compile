#include<stdio.h>
#include"add.h"

int main(int arg,char*argv[]){
	int ret = add(3,4);
	printf("main ret=%d\n",ret);
	return 0;
}
