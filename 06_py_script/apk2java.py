#! /usr/bin/python3
"""
1.依赖：
    1.需要下载jadx并配置环境变量
        下载地址: https://github.com/skylot/jadx
    2.需要安装python, 并配置环境变量
    3.jdk11, 并配置环境变量

2.jadx 参数说明：
    -e                  保存为android gradle工程
    --deobf             反混淆
    -d                  保存路径
    -j                  线程数; 默认4
    --show-bad-code     显示反编译失败的代码

jadx examples: 
    jadx SpeechHMI-debug.apk -e --deobf -d speech


3.本脚本使用
    ./apk2java.py  path  # path为指定的路径, 未指定的话则默认未当前路径
"""
import os
import re


# 执行cmd命令并返回结果
def execute_cmd(cmd):
    f = os.popen(cmd, "r")
    ret = f.read()
    f.close()
    return ret


def call_jadx(apks):
    all_size = len(apks)
    count = 0
    for apk_path in apks:
        apk_name = apk_path.split('/')[-1] #取数组最后一个元素, xxx.apk
        out_path = "out/" + apk_name[0:-4]
        cmd_apk2java = 'jadx\
            -e\
            -j 8\
            --deobf\
            --deobf-min 3\
            --deobf-max 64\
            --deobf-use-sourcename\
            --deobf-parse-kotlin-metadata\
            --deobf-cfg-file-mode read\
            --show-bad-code\
            -d %s  %s' % (out_path, apk_path)
        
        #cmd_apk2java = 'jadx -e -d %s -j 8 --show-bad-code %s' % (out_path, apk_path)

        count += 1
        print("%d/%d  decompile  %s ..." % (count, all_size, apk_name))
        execute_cmd(cmd_apk2java)

    print('finish !!!!!!!!!!!!!!!!!!')


if __name__ == "__main__":
    cmd_find_all_apk = "find . -name '*.apk'"
    apks = execute_cmd(cmd_find_all_apk).split()  #str转list

    call_jadx(apks)
