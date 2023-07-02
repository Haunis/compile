#! /bin/bash

#print使用：https://baijiahao.baidu.com/s?id=1717630495996240716&wfr=spider&for=pc

# 统计当前目录下，[[[所有文件夹]]]某个类型文件代码代码行数
# 如，统计sh文件代码行数： ./11_statistic.sh java  或者 ./11_statistic.sh abc_dir java

RED='\033[31m'
GREEN='\033[32;1m' #1是加粗字体
END='\033[0m'

function sub_file(){
	#注意符号是 esc按键的符号
	#echo '入参1-->'$1 #folder
	#echo '入参2-->'$2 #file_type

	count=0 #总代码行数
	for file in `ls $1` #将命令的结果作为变量
	do 
		if [ -d $1"/"$file ] #if后面方括号两边都要有空格
		then 	
			file_path=$1'/'$file 
			ret=`find $file_path -name '*.'$2|xargs cat |wc |awk '{print $1}'`
			count=`expr $count + $ret`

			# echo -e $file '\t\t' $ret '行' $2 '代码' #这样也可输入tab键，但效果不好
			# printf "|%-20s|\n" $file 
			printf "%-20s %-8d \n" $file_path $ret 
		# else
		# 	echo '****'
		fi
	done
	
	printf "\n%-22s %-8d \n" '总数' $count 
}

#echo "参数个数: $#"
if [[ $# = 1 ]];then
	folder="." #默认当前文件夹下
	file_type=$1
elif [[ $# = 2 ]];then
	folder=$1
	file_type=$2
else
	echo -e "${RED}请输入文件类型，如 sh,java !!!${END}"
	exit
fi


sub_file $folder $file_type #传入两个参数

