#! /usr/bin/python3
# -*-coding:utf-8-*-

import tkinter as tk
import os

w_win = 600  # 窗口宽度
h_win = 300  # 窗口高度

window = tk.Tk()
window.title('my window')
# window.geometry('600x300')
window.geometry(('%sx%s' % (w_win, h_win)))  # 窗口尺寸

e = tk.Entry(window, width=20, font=('黑体', 25), show=None)  # 如果是输入密码，可以写show='*'
# e.pack(side=tk.LEFT, padx=5, pady=5,expand=tk.YES, fill=tk.BOTH)
# e.pack(side=tk.TOP, padx=5, pady=25)
e.place(x=w_win // 2, y=35, anchor=tk.CENTER)  # entry的中心点放在(x,y)位置


# e.grid(row=0, padx=1, pady=1)

# t = tk.Text(window, bg='#ffffff',  width=40, height=2)
# t.place(x=w_win // 2, y=35, anchor=tk.CENTER)


def send():
    var = e.get()
    cmd = "adb shell am broadcast -a com.jiage.accessibility.test_action --es cmd %s" % var
    print("cmd-->",cmd)
    os.system(cmd)


def clean():
    e.delete(0, tk.END)


offset = 120  # 两个按钮关于中心点横坐标的偏移

b1 = tk.Button(window, text="发送", width=20, height=2, command=send)
b1.place(x=w_win // 2 - offset, y=180, anchor=tk.CENTER)
# b2.grid(row=1, column=0, padx=1, pady=4)


b2 = tk.Button(window, text="清除", width=20, height=2, command=clean)
# b2.grid(row=1, column=1, padx=1, pady=4)
b2.place(x=w_win // 2 + offset, y=180, anchor=tk.CENTER)

window.mainloop()  # 显示出来
