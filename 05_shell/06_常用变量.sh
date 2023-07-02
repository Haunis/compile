# $?保存上一次执行命令的结果;0--成功,1--失败

rm aaa.txt
ret=$?

if [ $ret = 0 ]; then
	echo ret:$ret,"执行成功"
else
	echo "无aaa.txt,执行失败"
fi


echo -e "\n---------------" #加上参数 -e 方可换行

echo "\$HOME: "$HOME	#家目录
#echo "\$PATH: "$PATH	#环境变量有那些



qnx_host=$QNX_HOST
sdp700=${qnx_host%/*/*/*}
env_sh=$sdp700"/qnxsdp-env.sh"
source $env_sh

