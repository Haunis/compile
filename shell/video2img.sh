#! /bin/bash
#将视频分帧

RED='\033[31m'
GREEN='\033[32;1m' #1是加粗字体
END='\033[0m'

declare -i have_video=0

dir=$(ls) #获取当前目录下所有文件
for file in $dir
do
#	echo $file
	if [ "${file##*.}" = "mp4" ] #等号两边注意有空格;注释和"]"要有空格
	then
		echo $file is video
		have_video=1
		ffmpeg -i $file -r 15 -f image2 %05d.bmp
		if [ $? = 0 ];then
			#echo -e "\033[32m----->>>convert ok<<<-----\033[0m"
			echo -e "${GREEN}---->>>convert ok<<<-----${END}"
		else
			echo -e "${RED}---->>>convert failed<<<-----${END}"
		fi
		break
	fi
done


if [ $have_video = 0 ]; then
	#echo -e "\033[31m无视频文件\033[0m"
	echo -e "${RED}无视频文件${END}"
fi
