#! /bin/bash

# $0--文件名
# $1--第一个参数
# $2--第二个参数
# $#--参数个数 ,不包括文件名

echo "文件名: $0"

echo "参数个数: $#"

if [[ $#>0 ]];then
	echo "第一个参数是: $1"
fi

count=1
while [ "$#" -ge "1" ];do
    echo "参数序号为 $count 是 $1"
    let count=count+1
    shift
done


