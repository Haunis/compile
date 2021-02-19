#! /usr/bin/python3

import os
import time
import datetime

for i in range(1):
	print(i)
	#cmd = "adb shell screencap -p /sdcard/screencap_" + datetime.datetime.now().strftime('%Y_%m_%d_%H_%M_%S')+".png"
	cmd = """
		adb shell "screencap -d 0 -p /mnt/sdcard/screen_shoot.png"
	"""
	os.system(cmd)
	time.sleep(2)

	cmd = """
	adb pull /mnt/sdcard/screen_shoot.png .
	"""
	os.system(cmd)
