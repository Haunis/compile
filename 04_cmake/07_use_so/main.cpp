#include<stdio.h>
#include"power.h"


int main(int argc,char *argv[]){
	printf("use so\n");
	int x = 3,y = 4;
	int result = power(3,4);
	printf("%d ^ %d = %d \n",x,y,result);
	return 0;
}
