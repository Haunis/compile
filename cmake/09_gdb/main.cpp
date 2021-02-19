#include<stdio.h>
#include<stdlib.h>
#include"config.h"

#ifdef USE_POWER
//	#include"math/power.h"
	#include<power.h>
#else
	#include<math.h>//系统头文件
#endif

//argc默认是1，argc是输入参数数量+1；
//argv[0]被占用，默认1开始存储输入的参数
int main(int argc,char* argv[]){
	
	printf("argc=%d\n",argc);
	if(argc<3){//如果输入参数少于2个的话，不继续执行
		printf("argv[0]=%s\n",argv[0]);
		return 1;
	}	
	double base = atof(argv[1]);	
	int exponent = atoi(argv[2]);
	double result;
	#ifdef USE_POWER
		printf("use power lib\n");
		result = power(base, exponent);
	#else
		printf("use standid lib\n");
		result = pow(base,exponent);
	#endif
	
	printf("%g ^ %d= %g\n", base,exponent,result);
	
	return 0;
}


