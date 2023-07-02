#! /bin/bash
home=$HOME
echo "home:"$home


qnx_host=$QNX_HOST
echo qnx_host:$qnx_host

sdp700=${qnx_host%/*/*/*}
echo "sdp700:" $sdp700

for file in `ls $sdp700`
do
	echo 'file in sdp700 : '$file
done


echo "---------------------"

env_sh=$sdp700"/qnxsdp-env.sh"
echo env_sh:$env_sh

#result=cat $env_sh
#echo $result

echo "source $env_sh"
source $env_sh

echo ""
env_sh_file_info=$(file $env_sh)
echo env_sh_file_info:$env_sh_file_info
