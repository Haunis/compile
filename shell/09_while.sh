
count=1

while (( $count<5 )) #必须两个括号
do
	echo $count
#	let "count++" #也行
	count=`expr $count + 1` # + 符号两边要有空格
done
