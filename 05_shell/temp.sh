#####! /bin/bash


#str="adbd is already running as root"
str="restarting adbd is already running as root"

len=`expr length "$str"`

echo "str 长度:"$len

restart="restarting"
#if [ $str != "" ]
#if [[ $str == *$restart* ]]
#if [[ $str =~ $restart || $str == "" ]]
if [[ $str =~ "restarting" || $str == "" ]]
then
	echo "true"
else
	echo "false"

fi

