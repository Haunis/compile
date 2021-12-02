#! /usr/bin/python3

import os
import time
import sys
import datetime


"""
参考： https://blog.csdn.net/fdipzone/article/details/24201113
"""

# 执行cmd命令并返回结果
def execute_cmd(cmd):
    # f = os.popen(r"adb devices", "r")
    f = os.popen(cmd, "r")
    ret = f.read()
    f.close()
    return ret


try_count = 0
def set_root_permission(): # 执行 adb root
    global try_count
    while True:
        cmd = "adb root"
        ret = execute_cmd(cmd)
        print("adb root: %s" % ret)
        # 为空就是未连接设备; out of date代表adb root还未执行成功
        if ret == '' or ret.find('out of date') >= 0 or ret.find('restarting') >= 0:
            print("sleep ---->", try_count)
            try_count += 1
            time.sleep(0.5)
            if try_count > 10:
                sys.exit()
        else:
            break


def get_now_date_cmd():
    t = time.localtime()  # time_struct

    year = t.tm_year # int 类型
    mon = t.tm_mon
    day = t.tm_mday
    hour = t.tm_hour
    minute = t.tm_min
    second = t.tm_sec
    #print("%d-%d-%d %d:%d:%d" % (year, mon, day, hour, minute, second))
	
    year = str(year) # 转成string类型
    mon = '0' + str(mon) if mon < 10 else str(mon)
    day = '0' + str(day) if day < 10 else str(day)
    hour = '0' + str(hour) if hour < 10 else str(hour)
    minute = '0' + str(minute) if minute < 10 else str(minute)
    second = '0' + str(second) if second < 10 else str(second)
    # cmd = "date 090110192021.36 set"
    cmd = "adb shell date %s%s%s%s%s.%s set" % (mon, day, hour, minute, year, second)

    return cmd

# 2021-01-01-08-03-02 
def get_input_date_cmd(s_date):
    li = s_date.split('-')
    year = li[0]
    mon = li[1]
    day = li[2]
    hour = li[3]
    minute = li[4]
    second = li[5]
    cmd = "adb shell date %s%s%s%s%s.%s set" % (mon, day, hour, minute, year, second)
    return cmd

if __name__ == "__main__":
    argv = sys.argv
    print("argv: ",argv)

    set_root_permission()
    
    if len(argv) > 1:
        cmd = get_input_date_cmd(argv[1]) 
    else:
        cmd = get_now_date_cmd()
    print("cmd = ", cmd)

    print("\npc时间： ",datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
    execute_cmd(cmd)


    cmd =""" adb shell "date +'%Y-%m-%d %H:%M:%S'" """
    print("\nandroid: ",execute_cmd(cmd))
    #os.system(cmd) 

