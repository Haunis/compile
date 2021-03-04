#include <stdio.h>
#include "add.h"
#include "power.h"

int add(int arg)
{

	int ret = (int)power(2, 3);
	printf("add --> ret = %d\n", ret);

	// int ret = arg + 1;
	// printf("add --> ret=%d\n", ret);
	return ret;
}
