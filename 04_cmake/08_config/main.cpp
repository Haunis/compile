#include<stdlib.h>
#include<stdio.h>

#include"config.h"//cmake生成的头文件

#ifdef USE_POWER
//	#include"math/power.h"
	#include"power.h"
#else
	#include<math.h>//系统头文件
#endif

int main(){
	double base = 2;
	int exponent = 4;
	double result;
	#ifdef USE_POWER
		printf("use 自定义power lib\n");
		result = power(base,exponent);
	#else
		printf("use 系统 lib\n");
		result = pow(base,exponent);
	#endif
	printf("%2.f ^ %d = %2.f\n",base,exponent,result);
	return 0;
}
