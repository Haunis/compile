/*
参考:https://www.cnblogs.com/electronic/p/10939769.html

*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handle(int arg){
	printf("\nhandle arg=%d\n",arg);
	
	kill(getpid(),9);	
}

int main(int argc,char*argv[]){
	//signal(SIGINT,handle);
	signal(SIGINT,SIG_IGN);//SIG_IGN 表示忽略信号
		
	sleep(7);
	printf("main exit\n");	
	return 0;
}
