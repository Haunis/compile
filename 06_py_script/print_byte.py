#! /usr/bin/python3
"""
打印二进制文件，前count个数值

使用: ./print_byte.py a1.pcm a2.pcm
"""

import sys


def do_print(file_names):
    print("file --> ", file_names)

    content_list = list()
    for f_name in file_names:
        f = open(f_name, 'rb')
        content = f.read()
        content_list.append(content)
        f.close()

    #打印每个文件前count个数
    count = 400
    for i in range(count):
        for content in content_list:
            print(content[i], end="\t")
        print()  #换行

if __name__ == "__main__":
    argv = sys.argv #列表 [文件名，参数1，参数2....]
    if len(argv) == 1:
        print("请输入文件名 ")
        sys.exit()
    else:
        do_print(argv[1:])
