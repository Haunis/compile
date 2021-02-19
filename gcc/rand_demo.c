#include <stdio.h>

int main(){
	while (1){
		sleep(1);
		int num = rand();//四字节,0~(2^32-1)之间
		printf("%d \n",num);
	}
	return 0;
}
