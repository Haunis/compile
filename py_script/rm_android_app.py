#! /usr/bin/python3 
"""
使用 os.popen(cmd, "r")可获取执行cmd后的输出
str_temp.find('abc') #str_temp中包含abc就返回0,否则返回-1
"""

import os
import re
import time
import sys


def get_cmd_ret(cmd):
    # f = os.popen(r"adb devices", "r")
    f = os.popen(cmd, "r")
    ret = f.read()
    f.close()
    return ret

try_count = 0
if __name__ == "__main__":
    # 1.先获取root权限
    while True:
        cmd = "adb root"
        ret = get_cmd_ret(cmd)
        print("adb root: %s"%ret)
        
        #为空就是未连接设备; out of date代表adb root还未执行成功
        if ret == '' or ret.find('out of date')>=0 or ret.find('restarting')>=0: 
            print("sleep ---->",try_count)
            try_count += 1
            time.sleep(0.5)
            if try_count >10:
                sys.exit()
        else:
            break

    # 2.查看 /data/app 下安装了哪些软件
    cmd = "adb shell ls /data/app"
    ret = get_cmd_ret(cmd)
    print("/data/app/:  \n%s" % ret)

    # 3.过滤/data/app/下有效的包名
    ret_list = ret.split()  # 将字分割成数组
    apps = list()
    for item in ret_list:
        ret = re.match(r"com[^-]*", item)  # com开头,后面0个或多个非"-"字符
        if ret is not None:
            apps.append(ret.group())

    # 4.卸载有效的包
    print("有效的安装软件:", apps)
    if len(apps) == 0:
        print("/data/app 无安装软件,无需卸载")
    else:
        for app in apps:
            cmd = "adb shell pm uninstall %s" % app
            ret = get_cmd_ret(cmd)
            print(ret)
        print("卸载完成!!!!!!!")
       
