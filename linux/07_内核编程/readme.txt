
/proc : 是个虚拟文件系统,可以访问内核的状态，进程的信息等
/proc/meminfo: 保存物理内存和交换空间的信息;可以使用cat 查看
/proc/kmsg: 各种级别的日志信息; 使用dmesg查看

插入模块：sudo insmod hello.ko
查看有哪些模块：lsmod
卸载模块：sudo rmmod hello
