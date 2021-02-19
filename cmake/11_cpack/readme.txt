在执行完cmake 和make命令之后可以使用cpack生成安装包
其实就是把头文件和lib库打包在一起

1.生成二进制或源码安装包
	二进制:cpack -C CPackConfig.cmake (会生成三个不同二进制包文件,三者内容相同)
	源码:cpack -C CPackSourceConfig.cmake

2.执行生成的二进制安装包 (以生成的.sh为例)
	sh demo6-1.0.1-Linux.sh
	该命令会在当前目录下生成demo6-1.0.1-Linux文件夹,执行该文件夹下/bin/main即可
	
