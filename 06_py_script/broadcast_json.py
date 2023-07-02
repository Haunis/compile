#! /usr/bin/python3
"""
1.创建json字符串
2.将json字符串通过adb broadcast发出去
"""
import json
import os


def gen_json():
    semantic = dict()
    semantic["service"] = "MUSIC_CONTROL"
    semantic["operation"] = "PAUSE"  # PLAY,NEXT,PAST,PAUSE
    semantic["song"] = "忘情水"
    # semantic["artist"] = "刘德华"

    out = dict()
    out["messageType"] = "REQUEST"
    out["focus"] = "music"
    out["needResponse"] = "YES"
    out["requestCode"] = "10001"
    out["version"] = "v1.0"
    out["operationApp"] = "speech"
    out["semantic"] = json.dumps(semantic, ensure_ascii=False)

    # 转换成json字符串
    return json.dumps(out, ensure_ascii=False)


if __name__ == "__main__":
    json_str = gen_json()
    json_str = json_str.replace(" ", "")[:-1]  # 最后一个'{'adb 广播发不出去，取消该符号
    cmd = "adb shell am broadcast -a com.yftech.voiceservice.test.receiver --ei func_code 2 --es json %s" % json_str
    print("cmd-->", cmd)
    os.system(cmd)
