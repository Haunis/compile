#include <stdio.h>
#include "power.h"
#include "add.h"

int main(int argc, char *argv[])
{
    int ret = (int)power(2, 3);
    printf("main ret = %d\n", ret);

    int add_ret = add(1);
    printf("main add_ret=%d\n", add_ret);
    return 0;
}