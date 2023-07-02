#! /usr/bin/bash

# https://blog.csdn.net/newchenxf/article/details/111376587
# 
# 播放pcm，使用ffmpeg工具ffplay:
# ffplay -f s16le -ar 16000 -ac 1 tmp.pcm
#     -f s16le: signed 16-bit little-endian; 可用ffmpeg -formats | grep PCM查看，一般16bit居多
#     -ar 16000: 采样率
#     -ac 1: 单声道
#


file=$1

ffplay -f s16le -ar 16000 -ac 1 $file



