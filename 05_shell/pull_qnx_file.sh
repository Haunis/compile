#! /usr/bin/bash

# 拉取qnx /root/下的文件
#需要先登录qnx,将根目录重新挂载为读写,并创建/root目录
#1. adb shell busybox telnet 10.0.0.2
#2. mount -o remount,rw /
#3. mkdir root
#4. screenshot;  会在当前路径下保存 screenshot.bmp


#echo "参数个数: $#"
if [[ $# = 1 ]];then
	file=$1
else
	echo -e "${RED}请输入文件名, 如 screenshot.bmp ${END}"
	exit
fi

adb root
adb remount

adb shell busybox ftpget -u root 10.0.0.2 /sdcard/$file /root/$file
adb pull /sdcard/$file .
