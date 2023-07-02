#! /usr/bin/python3

import os
import time

# 执行cmd命令并返回结果
def execute_cmd(cmd):
    # f = os.popen(r"adb devices", "r")
    f = os.popen(cmd, "r")
    ret = f.read()
    f.close()
    return ret

if __name__=="__main__":
    cmd = "adb shell procrank|grep speech"

    while True:
        time.sleep(0.5)
        ret = execute_cmd(cmd)
        print(ret)
