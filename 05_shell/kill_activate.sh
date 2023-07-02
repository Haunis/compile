RED='\033[31m'
GREEN='\033[32;1m' #1是加粗字体
END='\033[0m'


function do_kill(){ #定义执行kill 进程的函数
	ret=`adb shell ps |grep activate|awk '{print $2}'|xargs adb shell kill`
	ret_len=`expr length "$ret"`
	echo "ret_len:"$ret_len
	if [ $ret_len = 0 ]
	then
		echo -e "${GREEN}关闭activate进程成功 ${END}"
	else
		echo -e "${RED}activate 进程已经被关闭${END}"
		echo $ret
	fi	
}

function do_adb_root(){ #定义执行adb root的函数
	count=0
	while :
	do
		ret=`adb root`  #执行 adb root,并把执行结果保存在 ret
		last_ret=$? #上次执行的结果;0--成功,非0失败;本demo该方式失效..第一次明明失败,却返回0
		count=`expr $count + 1`
		#let "count++"
	
		echo "ret:"$ret
		echo "ret 长度:"`expr length "$ret"`
		echo "last_ret,\$?:"$last_ret
		#if [ $last_ret = 0 ] #第一次明明失败,却返回0;

		#注意if两个括号;
		#结果包含restarting,out,或者结果为空,则adb root执行失败
		if [[ $ret =~ "restarting" || $ret =~ "out" || $ret == "" ]]  
		then
			echo -e "${RED}adb root 失败 ${END}"
		else
			echo -e "${GREEN}adb root成功 ${END}"
			do_kill #调用do_kill()
			break
		fi
	
		#超过一定次数,停止运行		
		if [ $count -gt 10 ]
		then
			echo -e "${RED}超时 ...${END}"
			break
		fi
	    sleep 1 
	done 
}

do_adb_root #调用do_adb_root()
