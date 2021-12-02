https://www.cnblogs.com/wanghuaijun/p/7624564.html
https://www.cnblogs.com/yueshangzuo/p/8078687.html



make    //编译驱动

insmod mmap_driver.ko    //安装驱动
mknod /dev/mmap_driver c 999 0    //创建设备文件


gcc test_mmap.c -o test.o    //编译应用程序
./test.o    //运行应用程序来测试驱动程序;  这里运行失败。。


