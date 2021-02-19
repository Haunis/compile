#convert GB2312 to UTF-8,when use file from windows to linux

declare -i index=0 #定义整数,表示存放文件名的数组索引
arrayFile=() #定义一个数组,存放文件名

dir=$(ls) #获取当前目录下所有文件
for file in $dir
do
#       echo $index : $file
        arrayFile[$index]=$file #将文件名存放在数组
        index=$index+1
done

#for file  in ${arrayFile[@]}
#do
#       echo array:$file 
#done

for((i=0;i<${#arrayFile[@]};i++))do
        echo $i :  ${arrayFile[i]}
done

echo -n "please input file number: "
read fileNum

if (($fileNum>=${#arrayFile[@]-1}));then 
	echo -e "\033[31m please input num less than ${#arrayFile[@]} \033[0m"
	exit 0;
fi

#echo ${#arrayFile[@]}

fileName=${arrayFile[fileNum]}
des=result$fileName 

encode=$(file $fileName) #查看该文件信息
#echo $encode

echo "convert ":$fileName
iconv -f GB2312 -t UTF-8 $fileName -o $des
echo -e "\033[32m covert succss : $des \033[0m"
