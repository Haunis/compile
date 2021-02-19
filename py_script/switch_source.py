#! /usr/bin/python3

import os
import time
import signal
import subprocess
import threading

def handler(signum, frame):
    print("接受到了 ctrl c:", signum, frame)
    exit(0)



	
if __name__=="__main__":
	signal.signal(signal.SIGINT, handler)  
	
	# t = threading.Thread(target=func)
	# t.start()

	cmd = """ 
		adb shell am broadcast -a com.living.subdisplayservice.demo.keyevent --ei keycode 15 --ei data 1
	"""

	for i in range(50):
		print("=======>",i)
		os.system(cmd)
		time.sleep(0.05)
		print("pid,",os.getpid())

