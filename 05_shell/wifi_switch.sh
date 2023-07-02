#! /usr/bin/bash

#参考： https://blog.csdn.net/fdipzone/article/details/24201113
# 		https://blog.csdn.net/qydjss/article/details/127693829

function check_wifi_s(){
	sleep $1
	nmcli dev status #查看网络设备状态
}

function turn_on_wifi(){
	sleep $1 
	echo  -e "\n开启时间:" `date '+%Y-%m-%d %H:%M:%S'` 
	nmcli radio wifi on # 打开wifi

	check_wifi_s 10
}

function turn_off_wifi(){
	sleep $1 
	echo -e "\n关闭时间:" `date '+%Y-%m-%d %H:%M:%S'` 
	nmcli radio wifi off # 打开wifi

	check_wifi_s 1
}

turn_off_wifi 1  #多长时间以后关闭wifi
turn_on_wifi 10 #多长时间以后开启wifi
