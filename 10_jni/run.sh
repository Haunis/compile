#! /usr/bin/bash

# ./run.sh c 或者 ./run.sh cpp


RED='\033[31m'
GREEN='\033[32;1m' #1是加粗字体
END='\033[0m'

#1.编译java文件
javac com/jiage/Demo.java 


#2.编译so库
if [[ $1 = "cpp" ]];then
	echo "start compile cpp"
	gcc -shared -I /opt/java-7-openjdk-amd64/include -fPIC test.cpp -o lib/libjni-test.so
elif [[ $1 = "c" ]];then
	echo "start compile c"
	gcc -shared -I /opt/java-7-openjdk-amd64/include -fPIC test.c -o lib/libjni-test.so
else
	echo -e "${RED}no file to compile -->$1<-- ,input 'c' or 'cpp' ${RED}"
	exit 0
fi

#3.运行java程序
echo -e "start run ...\n"
java -Djava.library.path=lib com.jiage.Demo


