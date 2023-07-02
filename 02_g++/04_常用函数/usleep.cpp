#include<stdio.h>
#include<unistd.h>

int main(int argc,char*argv[]){

	while(1){
		printf("usleep 和sleep一样,需要导入unistd.h \n");
		usleep(1*1000*1000);//1s
	}
	return 0;
}
