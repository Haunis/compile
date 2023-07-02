#! /usr/bin/python3
"""
pcm转wav:
    https://blog.csdn.net/shenyunmomie/article/details/126138648

int转byte:
    https://blog.csdn.net/qq_33210042/article/details/118303233

    (8).to_bytes(1, 'big') # 8转byte类型; 1--1个字节，big--大端
"""

import sys


def gen_wav_head(audio_len, file_len, sample_rate, channels):
    bits_per_sample = 16  #取样位元深度
    byte_rate = (bits_per_sample * sample_rate * channels // 8)  #位元(组)率

    header = [(0).to_bytes(1, 'big')] * 44
    header[0] = b'R'  # RIFF/WAVE header
    header[1] = b'I'
    header[2] = b'F'
    header[3] = b'F'

    header[4] = (file_len & 0xff).to_bytes(1, 'big')  #fileLength;总大小
    header[5] = ((file_len >> 8) & 0xff).to_bytes(1, 'big')
    header[6] = ((file_len >> 16) & 0xff).to_bytes(1, 'big')
    header[7] = ((file_len >> 24) & 0xff).to_bytes(1, 'big')

    header[8] = b'W'  #wavTag; 文件格式
    header[9] = b'A'
    header[10] = b'V'
    header[11] = b'E'

    header[12] = b'f'  # 子区块1标签, 'fmt'
    header[13] = b'm'
    header[14] = b't'
    header[15] = b' '
    header[16] = (16).to_bytes(1, 'big')  # 子区块1大小，16
    header[17] = (0).to_bytes(1, 'big')
    header[18] = (0).to_bytes(1, 'big')
    header[19] = (0).to_bytes(1, 'big')

    header[20] = (1).to_bytes(1, 'big')  # format = 1; 音频格式1(pcm)
    header[21] = (0).to_bytes(1, 'big')

    header[22] = channels.to_bytes(1, 'big')  # 声道数; 1-单声道， 2-立体声
    header[23] = (0).to_bytes(1, 'big')

    header[24] = (sample_rate & 0xff).to_bytes(1, 'big')  # 取样点/秒, Hz
    header[25] = ((sample_rate >> 8) & 0xff).to_bytes(1, 'big')
    header[26] = ((sample_rate >> 16) & 0xff).to_bytes(1, 'big')
    header[27] = ((sample_rate >> 24) & 0xff).to_bytes(1, 'big')

    header[28] = (byte_rate & 0xff).to_bytes(1, 'big')  #位元(组)率； AvgBytesPerSec
    header[29] = ((byte_rate >> 8) & 0xff).to_bytes(1, 'big')
    header[30] = ((byte_rate >> 16) & 0xff).to_bytes(1, 'big')
    header[31] = ((byte_rate >> 24) & 0xff).to_bytes(1, 'big')

    # header[32] = (2 * 16 / 8).to_bytes(1, 'big')  #block align
    header[32] = (channels * bits_per_sample // 8).to_bytes(1, 'big')  # block align； 区块对齐
    header[33] = (0).to_bytes(1, 'big')

    header[34] = bits_per_sample.to_bytes(1, 'big')  # 取样位元深度
    header[35] = (0).to_bytes(1, 'big')

    header[36] = b'd'  #子区块2标签； DataHdrID
    header[37] = b'a'
    header[38] = b't'
    header[39] = b'a'
    header[40] = (audio_len & 0xff).to_bytes(1, 'big')  #子区块2大小； DataHdrLeth
    header[41] = ((audio_len >> 8) & 0xff).to_bytes(1, 'big')
    header[42] = ((audio_len >> 16) & 0xff).to_bytes(1, 'big')
    header[43] = ((audio_len >> 24) & 0xff).to_bytes(1, 'big')

    return header


def pcm2wav(pcm_file, sample_rate, channels, out_file):
    with open(pcm_file, 'rb') as f:
        pcm_data = f.read()
        audio_len = len(pcm_data)
        print('audio_len = ', audio_len)

    file_len = audio_len + (44 - 8)
    head = gen_wav_head(audio_len, file_len, sample_rate, channels)
    # for i in range(len(head)):
    #     print(i, '-->', head[i])

    with open(out_file, 'wb') as f:
        f.write(b''.join(head))
        f.write(pcm_data)
        
    print("pcm 2 wav success --> ", out_file)


if __name__ == "__main__":
    if len(sys.argv) >= 2:  #文件名，参数1，参数2....
        in_file = sys.argv[1]
        print("pcm file --> ", in_file)
    else:
        print("请输入pcm文件名")
        exit()

    sample_rate = 44100  #采样率， 16000，44100...
    channels = 1  # 1-单声道， 2-立体声
    out_file = 'ret.wav'

    pcm2wav(in_file, sample_rate, channels, out_file)
