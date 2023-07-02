参考：https://blog.csdn.net/sxj731533730/article/details/84345505

静态链接库的生成和使用

生成：
1.在要编译成静态库的文件夹(math)生成目标文件
    g++ -c -o add.o add.cpp
2.根据生成的目标文件生成静态库文件
    ar -crv libadd.a add.o (-c：创建，r:向add.a插入add.o v:附加信息)

使用：
1.在要使用静态的文件目录生成目标文件
    g++ -c -o main.o  main.cpp
2.将生成额目标文件和静态库文件链接起来
    方式1:g++ -o main main.o math/libadd.a
    方式2:g++ -o main main.o -L./math -ladd
          -L: 表示要链接的库的令
         -ladd: 要链接的库名,libadd.a

