
#目标文件; 保持和task_struct.c文件名一致
obj-m:=task_struct.o 

#模块所在路径
CURRENT_PATH:=$(shell pwd)

LINUX_KERNEL:=$(shell uname -r)

LINUX_KERNEL_PATH:=/usr/src/linux-headers-$(LINUX_KERNEL)

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules  # modules表明编译的是内核模块

clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean 
