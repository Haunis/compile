#include<stdio.h>
#include<iostream>
#include "string.h"  
#include "stdio.h"  
#include "stdlib.h"  

using namespace std;

int main(int argc,char*argv[]){
	// int a = 10;
	// int b = 20;

	// printf("a = %d\n",a);
	// printf("b = %d\n",b);
	// std::swap(a,b);	
	// printf("a = %d\n",a);
	// printf("b = %d\n",b);

	// int *p = 0;
	// *p = 1; //will seg fault

	printf("before run abort!\n");
	abort();  
    printf("after run abort!\n"); 

	return 0;
}
