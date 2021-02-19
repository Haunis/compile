#将当前文件夹下所有.java .sh转为utf-8编码

#定义一个函数
function traverse(){
	#注意符号是 esc按键的符号
	for file in `ls $1` #将命令的结果作为变量
	do 
		if [ -d $1"/"$file ] #if后面方括号两边都要有空格
		then 	
			traverse $1"/"$file
		#	echo $1"/"$file
		else
			path=$1"/"$file
			if [ "${path##*.}" = "java" ]||[ "${path##*.}" = "sh" ] #等号两边注意有空格;注释和"]"要有空格
			then
				fileName=`basename $file` #basename是提取文件名的关键字;这里fileName这个变量下问没用到

				fileInfo=$(file $path) #这里file是个命令;获取文件信息如： allToUtf8.sh: UTF-8 Unicode text
				encodeInfo=${fileInfo##*:} #截取最右边"："的字符串，如：UTF-8 Unicode text
				
				encode=$encodeInfo #将一个变量赋给一个新变量				
				if [[ $encodeInfo == *,* ]];then #encodeInfo包含","
					encode=${encodeInfo%,*} #从左边起截取第一个","左边的字符串
					if [[ $encode == *,* ]];then #encode 还包含","
						encode=${encode##*,} #从左边开始，截取最右边","右边的字符串
					fi
				fi

				if [[ $encodeInfo != *UTF-8* ]];then
					echo $path : $encode
					iconv -f GB2312 -t UTF-8 $path -o $path
				else
					echo -e "\033[32m $path : $encode,已是UTF-8编码    \033[0m"
				fi 
				

			fi
		fi
	
	done
}

folder="."
traverse $folder
