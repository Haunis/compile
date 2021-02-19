#include<stdio.h>
#include<unistd.h>

int main(int argc,char*argv[]){

	while(1){
		printf("sleep 需要导入unistd.h \n");
		sleep(1);
	}
	return 0;
}
