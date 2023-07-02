#include<stdlib.h>
#include<stdio.h>

double power(double base ,int exponent){
	if(exponent==0){
		return 1;
	}
	double result = base;
	for(int i = 1;i<exponent;++i){
		result = result *base;
	}
	return result;
}
int main(int argc,char*argv[]){
	if(argc<3){
		printf("argv[0]=%s\n",argv[0]);
		printf("请输入基数和指数\n");
		return 0;
	}	
	

	double base = atof(argv[1]);
	int exponent = atoi(argv[2]);
	double result = power(base,exponent);
	printf("%.2f ^ %d = %.2f\n",base,exponent,result);
	return 0;
}
