#include <stdio.h>
#include <stdlib.h>
//#include "config.h"
#include <config.h>

#ifdef HAVE_POW
	#include <math.h>
#else
	#include "power.h"		
#endif

int main(int argc,char* argv[]){
	printf("argc=%d\n",argc);
    if(argc<3){//如果输入参数少于2个的话，不继续执行
        printf("argv[0]=%s\n",argv[0]);
		printf("version = %d.%d\n",Demo_VERSION_MAJOR,Demo_VERSION_MINOR);
        return 1;
    }
    double base = atof(argv[1]);
    int exponent = atoi(argv[2]);
    double result;
#ifdef HAVE_POW 
    printf("use standid lib\n");
    result = power(base, exponent);
#else
	printf("use my power lib\n");
    result = power(base,exponent);
#endif
 
    printf("%g ^ %d = %g\n", base,exponent,result);
  
    return 0;
}


