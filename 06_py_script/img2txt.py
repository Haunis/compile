#! /usr/bin/python3

from PIL import Image # PIL 是一个 Python 图像处理库

WIDTH = 60*8 # 字符画的宽
HEIGHT = 28*8 # 字符画的高

# 将256灰度映射到70个字符上，也就是RGB值转字符的函数：
def get_char(r, g, b, alpha=256):  # alpha透明度
   # 图片映射所用的字符集，一共有 70 个字符，字符的种类与数量可以自己根据字符画的效果反复调试的
   ascii_char = list("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")
   length = len(ascii_char)
   gray = int(0.2126 * r + 0.7152 * g + 0.0722 * b)  # 计算灰度
   x = int (gray / 256.0  * length) #利用占比关系映射
   #return ' ' if gray>125 else '0' 
   return ascii_char[x]  # 不同的灰度对应着不同的字符, 通过灰度来区分色块
  

if __name__ == '__main__':
   img = '1.jpg' # 图片所在位置
   im = Image.open(img)
   im = im.resize((WIDTH, HEIGHT))  #将图片缩放至一定的尺寸
   txt = ""
   for i in range(HEIGHT):
       for j in range(WIDTH):
           txt += get_char(*im.getpixel((j, i))) # 获得相应的字符
       txt += '\n' #每行映射完毕换行

   print(txt)  # 打印出字符画

   # 将字符画 写入文件中
   txt_path = img.split('.')[0]+'.txt' 
   with open(txt_path, 'w') as f:
       f.write(txt)

