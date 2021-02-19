#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int arg,char** args){
	char msg[] ="hello";
	char msg2[] =msg+2;
	printf("%s",msg2);
	return 0;
}
