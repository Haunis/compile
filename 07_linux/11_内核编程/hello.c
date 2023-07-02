#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

//编译修饰符，告诉编译程序这个模块执行完之后，回收内存空间
static int __init lkp_init(void){
	printk("hello from kernel space \n");
	return 0;
}

static void __exit lkp_exit(void){
	printk("bye kernel space \n");
	//return 0;
}


module_init(lkp_init);
module_exit(lkp_exit);

//模块的许可声明GPL
MODULE_LICENSE("GPL");
