/*
 * 参考: https://www.cnblogs.com/wuyepeng/p/9748889.html
 * 共享内存没有同步和互斥机制,所以要使用信号量实现对共享内存存取的同步
 *
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include "shmdata.h"
int main()
{
    int running = 1;              // 程序是否继续运行的标志
    void *origin_shm = NULL;      // 分配的共享内存的原始首地址
    struct shared_use_st *shared; // 指向shm
    int shmid;                    // 共享内存标识符
    /*
    ******************第1步:创建共享内存**********************
    获取共享内存id
    参数1:非零长整型;让两个进程看到同一个信号集
    参数2:指定共享内存大小;一般是一页大小的整数倍
    参数3:标识位;IPC_CREATE:现在就打开 IPC_CREATE|IPC_EXCL:创建一个新的
    */
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    /*
    ******************第2步:将共享内存地址链接到当前进程内存空间**********************
    可以理解shmat申请一块内存区域,返回内存首地址
    参数1:shm_id是由shmget函数返回的共享内存标识
    参数2:shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址
    参数3:shm_flg是一组标志位，通常为0
    */
    origin_shm = shmat(shmid, 0, 0);
    if (origin_shm == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("\nMemory attached at %X\n", (int)origin_shm);
    // 设置共享内存;
    shared = (struct shared_use_st *)origin_shm;
    printf("shared:%#x\n", shared);
    //	sleep(10);
    shared->written = 0; // 设置为0,使得共享内存可写

    //******************第3步:从共享内存获取数据**********************
    while (running) // 读取共享内存中的数据;都是非阻塞的,所以循环里的代码会一直在执行
    {
        printf("loop......\n");
        if (shared->written != 0) // 没有进程向共享内存定数据有数据可读取;非0可读,0可写
        {
            printf("receive.... \n");
            char *s = shared->text;
            printf("receive :%s\n", s);
            sleep(rand() % 3);
            shared->written = 0;                      // 读取完数据，设置written使共享内存段可写
            if (strncmp(shared->text, "end", 3) == 0) // 输入了end，退出循环（程序）
                running = 0;
        }
        else // 有其他进程在写数据，不能读取数据
            sleep(1);
    }
    // 把共享内存从当前进程中分离;
    // 该操作不从系统中删除标识符和其数据结构,要显示调用shmctl(带命令IPC_RMID)才能删除它
    if (shmdt(origin_shm) == -1)
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    /*
    删除共享内存
    参数1:shmget()返回的共享内存标识符
    参数2:IPC_STAT--把shmid_ds结构中的数据设置为共享内存的当前关联值
                     即用共享内存的当前关联值覆盖shmid_ds的值
          IPC_SET:如果进程有足够的权限,就把共享内存的当前关联值设置为
                    shmid_ds结构中给出的值
          IPC_RMID:删除共享内存段
    */
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
