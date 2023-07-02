declare -i haveDebugApk=0
dir=$(ls)
for file in $dir
do
        echo $count : $file
	if [ app-debug.apk == $file  ];then
		haveDebugApk=$haveDebugApk+1
	fi
done
echo haveDebugApk:$haveDebugApk
if [ 0 -eq $haveDebugApk ];then #没有app-debug.apk文件就退出
	echo -e "\033[31m no app-debug.apk \033[0m"
	exit 0;	
fi

rm DeviceInteractionService.apk
mv app-debug.apk DeviceInteractionService.apk


echo "run as root"
adb root
adb shell "mount -o remount,rw /system"
#删除系统目录apk
adb shell "rm /system/priv-app/DeviceInteractionService/DeviceInteractionService.apk"
echo "rm completed"
adb push DeviceInteractionService.apk /system/priv-app/DeviceInteractionService
echo "push completed"
