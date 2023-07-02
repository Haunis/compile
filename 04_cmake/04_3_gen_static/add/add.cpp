#include <stdio.h>
#include "add.h"
#include "power.h" //在主CMakeLists.txt中已include power.h,所以这里可以直接使用

int add(int arg)
{

	int ret = (int)power(2, 3);
	printf("add --> ret = %d\n", ret);

	// int ret = arg + 1;
	// printf("add --> ret=%d\n", ret);
	return ret;
}
