#include<stdlib.h>
#include<stdio.h>

//#include"math/power.h"//使用的静态库所在的路径

//需要CMakeLists.txt设置include_directories("${PROJECT_SOURCE_DIR}/math")
//才可以不用写完整路径
#include"power.h"

int main(int argc,char* argv[]){
	printf("argc=%d\n",argc);
	if(argc<3){//如果输入参数少于2个的话，不继续执行
		printf("argv[0]=%s\n",argv[0]);
		return 1;
	}	
	double base = atof(argv[1]);	
	int exponent = atoi(argv[2]);
	double result =  power(base,exponent);
	printf("%g ^ %d = % g\n",base,exponent,result);
	
	return 0;
}

