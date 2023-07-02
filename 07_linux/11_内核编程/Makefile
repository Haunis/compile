
obj-m := hello.o #使用hello.o建立模块

CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r) #内核版本
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL) #内核源代码路径

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules #编译模块
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean #清理模块
