#include<stdio.h>
#include<stdlib.h>

#include"math/add.h"

int main(int argc , char *argv []){
	int x = 3,y =4;
	int result = add(x,y);
	printf("main %d + %d = %d \n ",x,y ,result);
}
