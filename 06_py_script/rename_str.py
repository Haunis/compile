#! /usr/bin/python3
"""
把某个类型文件里的所有字符串替换成新的字符串

使用： ./rename_str.py java class clazz  (文件后缀名，旧字符串，新字符串)
"""

import os
import sys

# 执行cmd命令并返回结果
def execute_cmd(cmd):
    # f = os.popen(r"adb devices", "r")
    f = os.popen(cmd, "r")
    ret = f.read()
    f.close()
    return ret

def rename_str(files, old_str, new_str):
    for file_name in files:
        ret = None
        with open(file_name,'r') as f:
            data = f.read()
            if old_str in data:
                print('f--> ',file_name)
                ret = data.replace(old_str, new_str)
                #f.seek(0)  # 文件指针回到初始位置
                #f.write(' ' * len(data)) #先将文件内容置空
                #f.seek(0)  
                #f.write(ret) #再写入真正想写的内容

        if ret is not None: #新建文件，覆盖原文件
            with open(file_name,'w') as f:
                f.write(ret)
            
if __name__=="__main__":
    file_type = "java"
    old_str = "a"
    new_str = "x"

    argv = sys.argv #文件名，参数1，参数2....
    if len(argv) > 3:
        file_type, old_str, new_str = argv[1], argv[2],argv[3]
        print("file_type:", file_type)
        print("str: %s --> %s "%( old_str, new_str))
    else:
        print('请输入：文件后缀名， 旧字符串， 新字符串')
        sys.exit()

    cmd = "find . -name '*.%s'"%file_type
    files = execute_cmd(cmd)
    #print("files:  ", files)
    rename_str(files.split(), old_str, new_str)
