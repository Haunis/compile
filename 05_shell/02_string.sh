# if [[ $str == "" ]]  -- 判断字符串是否为空
# if [[ $str =~ "restarting"]]  --判断字符串是否包含后面的字符串
# `expr length "$str"` --获取字符串长度


str="restarting adbd is already running as root"

echo "str:"$str

len=`expr length "$str"`
echo "str 长度:"$len

sub_str="restarting"
if [[ $str =~ $sub_str || $str == "" ]]
then
	echo "包含:"$sub_str
else
	echo "不包含:"$sub_str
fi

