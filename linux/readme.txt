1. 编译.c文件详细步骤
    参考：https://blog.csdn.net/rabbit_zhen/article/details/87212887
    gcc -E hello.c -o xxx       //预处理
    gcc -S hello.c -o hello.s   //编译,得到汇编代码
    gcc -c hello.s -o hello.o   //汇编,得到机器码
    gcc hello.c -o hello        //链接

    反汇编:
    objdump -d hello