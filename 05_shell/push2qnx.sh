#! /usr/bin/bash

#需要先登录qnx,将根目录重新挂载为读写,并创建/root目录
#1. adb shell busybox telnet 10.0.0.2
#2. mount -o remount,rw /
#3. mkdir root

adb root
adb remount

file=$1
if [ "$file" = "" ]; then
	echo "no file !!!"
	exit	
else
	echo "file-->"$file
fi


file_name=${file##*/}  #截取最右边"/"右边的的字符,也就是真实的文件
echo "file_name-->"$file_name


adb push $file /sdcard/
echo "push $file_name to qnx ...."
adb shell busybox ftpput -u root 10.0.0.2 /root/$file_name /sdcard/$file_name
