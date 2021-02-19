/**
 参考:/binder/IPCThreadState.cpp
*/

#include <stdio.h>

#define IF_LOG_TRANSACTIONS() if (true)
#define INCREASE(x) x+1

int main(int arg,char*argv[]){
	
	IF_LOG_TRANSACTIONS(){
		printf("IF_LOG_TRANSACTIONS executed \n");
	}

	int a = 1;

	printf("before INCREASE a=%d\n",a);	
	a = INCREASE(a);
	printf("after INCREASE a=%d\n",a);	
}

