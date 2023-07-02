#-1仪表截屏
#可以不用root权限
rm screen_shoot.png
#echo "run as root"
#adb root
adb shell "screencap -d 0 -p /mnt/sdcard/screen_shoot.png"
sleep 1s
adb pull /mnt/sdcard/screen_shoot.png .
