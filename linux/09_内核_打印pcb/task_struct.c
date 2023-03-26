/*
 * 打印pcb(Process Control Block)相关信息
 *
 * 设置includePath(关联头文件和实现文件):
 *      打开命令面板 ctrl+shift+p,输入configuration; 选择 C/C++:Edit Configurations
 *
 * 参考：https://www.icourse163.org/learn/XIYOU-1461809182?tid=1470028455#/learn/content?type=detail&id=1252983750&cid=1282961445&replay=true
 *
 * 编译： make
 *
 * 装载内核模块： sudo insmod task_struct.ko
 * 查看系统模块： lsmod
 * 查看内核信息： dmesg
 * 删除内核模块： sudo rmmod task_struct
 *
 */

#include <linux/module.h> //使用 locate linux/module.h 查看头文件在哪，然后在c_cpp_properties.json包含进来
#include <linux/kernel.h>
#include <uapi/linux/sched.h>
#include <linux/init_task.h>
#include <linux/init.h>
#include <linux/fdtable.h>

MODULE_LICENSE("GPL");

// 内核模块初始化函数
static int __init print_pid(void)
{
    struct task_struct *task, *p;
    struct list_head *pos; // 双向链表指针
    int count = 0;         // 有多少进程
    printk("print msg begin : \n");

    task = &init_task; // 0号闲逛进程

    // 遍历进程列表; 遍历&task->tasks链表，初始指针是pos
    list_for_each(pos, &task->tasks)
    {
        // 第一个参数pos代表tasks的地址, 第二个参数是结构体类型
        p = list_entry(pos, struct task_struct, tasks);
        count++;
        printk("\n\n");
        printk("pid:%d prio:%d static_prio:%d \n", p->pid, p->prio, p->static_prio);
    }
    printk("进程个数： %d\n", count);

    return 0;
}

static void __exit lkp_exit(void)
{
    printk("bye kernel space \n");
    // return 0;
}

module_init(print_pid);
module_exit(lkp_exit);
