#! /usr/bin/bash

# aosp生成img路径：bin/mydroid/out/target/product/xxx/ 

# ramdisk.img,ramdisk-recovery.img:
# 	https://blog.csdn.net/conowen/article/details/7251057
#	file查看结果:gzip compressed data
# 	这些映像文件是采用cpio打包、gzip压缩的

# boot.img: 
#	https://blog.csdn.net/lhl_blog/article/details/82494399
#	file查看结果：Android bootimg

# system.img
#	https://www.shangmayuan.com/a/29e2f2f090964a6689fb412f.html
#	file 查看结果: Android sparse image
#	由于是挂载的方式访问，所以注意要取消挂载sudo umount sparse_system
#
#	simg2img工具安装：
#		1.https://blog.csdn.net/u010285974/article/details/105268744 
#			wget https://github.com/anestisb/android-simg2img/archive/master.zip
#			make
#		2.aosp源码下 out/host/linux-x86/bin/simg2img, 使用时提示缺少so库
#



# Android 系统目录
# 参考：
#	https://www.cnblogs.com/pixy/p/4744501.html
#	https://blog.csdn.net/conowen/article/details/7251057
#	
#	android编译后源码输出：bin/mydroid/out/target/product/xxx/
#	system.img,ramdisk.img,userdata.img映像文件是采用cpio打包、gzip压缩的
#	
#	ramdisk.img：是一个分区映像文件，即是一个文件系统（root file system），kernel启动时，ramdisk负责init
#	system.img： 包括了主要系统，系统app等，挂载于文件系统下的system文件夹
#	userdata.img: 包括了一些用户数据，被挂载到文件系统下的data文件夹下。
#	
#	Android源码编译后的目录：
#	root： ramdisk.img解压后的内容，即是一个文件系统，包括system、data、bin、dev等目录。
#	system：system.img解压后的内容
#	data：userdata.img的解压后的内容


function ungz_img(){ #ramdisk.img
	echo "start extract  gz ...$1"
	dir='gz_'${inputfile%.*}	  #删除右边字符，保留左边字符--从右边开始删，一直删到.
	mkdir $dir
	cp $inputfile $dir
	cd $dir
	gzfile=$inputfile.gz
	mv $inputfile $gzfile		  #重命名为.gz文件，gunzip才开解压

	gunzip $gzfile				  #解压
	#cpio -i -F $inputfile -D aaa #解包到aaa
	cpio -i -F $inputfile		  #解包
	rm $inputfile
}

function unsparse_img(){ #system.img, userdata.img
	echo "start extract sparse...$1"
	dir='sparse_'${inputfile%.*}  #删除右边字符，保留左边字符--从右边开始删，一直删到.
	mkdir $dir
	ext4file=$inputfile.ext4
	simg2img $inputfile $ext4file   # out/host/linux-x86/bin/simg2img 下的工具？
	sudo mount -t ext4 -o loop $ext4file  $dir 
}

function unboot_img(){
	echo "未加入 boot.img解析功能"
}

inputfile=$1
file_info=$(file $inputfile)

if [[ $file_info =~ "Android bootimg" ]]; then
	unboot_img $inputfile
elif [[ $file_info =~ "gzip compressed" ]]; then
	ungz_img $inputfile
elif [[ $file_info =~ "Android sparse" ]]; then
	unsparse_img $inputfile
else
	echo "no -->"$file_info
fi


