#include <stdio.h>
#include "add.h"

int add(int x,int y){
	printf("add called x=%d,y=%d\n",x,y);
	return x+y;
}
