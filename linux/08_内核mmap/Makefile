#ifneq ($(KERNELRELEASE),)  
#  
#obj-m := mmap_driver.o  
#@echo "not release." 
# 
#else  
#KDIR := /lib/modules/4.15.0-142-generic/build
#  
#all:  
#	make -C $(KDIR) M=$(PWD) modules  
#clean:  
#	rm -f *.ko *.o *.mod.o *.mod.c *~ *.symvers *.order  
#  
#endif  



obj-m := mmap_driver.o  #使用mmap_driver.o建立模块

CURRENT_PATH := $(shell pwd)
LINUX_KERNEL := $(shell uname -r) #内核版本
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(LINUX_KERNEL) #内核源代码路径

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules #编译模块
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean #清理模块
