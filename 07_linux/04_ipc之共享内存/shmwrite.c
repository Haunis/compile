/**
 *
 * 1.创建共享区
 * int shmeget(key_t key, size_t size, int shmflg) //头文件:<sys/ipc.h>,<sys/shm.h>
 *      key:两个进程持有相同的key，就可以共同访问共享内存区
 *          两种情况会为shmget创建一块新的内存共享区：
 *          1.key=IPC_PRIVATE
 *          2.key不是IPC_PRIVATE,但shmflg指定了IPC_CREATE标志
 *      size:共享区大小，以字节为单位；linux下是页的整数倍
 *      shmflg:
 *          IPC_CREATE:申请新建区域
 *          IPC_EXCL:和IPC_CREATE共同使用，如果指定区域已经存在，则返回错误
 *          mode_flags:参照open函数中的mode参数
 *          SHM_HUGETLB:使用“huge_pages”机制申请，linux2.6后版本优先
 *          SHM_NORESERVE:此区域不保留swap控件
 *      返回值：内存共享区域id值，用于唯一标识该区域
 *
 * 2.映射共享内存到本进程空间
 * char* shmat(int shmid, void *shmaddr,int shmflg)
 *      shmid:共享区id值
 *      shmaddr:将共享内存区映射到指定地址； 可以为0，此时自动分配地址
 *      shmflg:同shmget
 *      返回值：返回该内存区起始地址
 *
 * 3.撤销内存映射区
 * 完成进程间通信后，各个进程需要撤销之前的映射操作
 * int shmdt(char *shmaddr)
 *      shmaddr: 同shmat,共享内存映射到本进程的地址
 *
 * 4.删除共享内存
 * int shmctl(int shmid,int cmd, struct shmid_ds *buf)
 *      shmid:同shmget返回值，共享内存区id
 *      cmd：
 *          IPC_STAT:状态查询，结果存入buf中
 *          IPC_SET:在权限允许的情况下，将共享内存状态更新未buf中的数据
 *          IPC_RMID:删除共享内存段
 *      buf：如上所述
 *      返回值：0表示成功，否则失败
 *
 * 
 * 
 * 编译：gcc -o write shmwrite.c
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shmdata.h"
int main()
{
    int running = 1;
    void *origin_shm = NULL;
    struct shared_use_st *shared = NULL;
    char buffer[BUFSIZ + 1]; //用于保存输入的文本
    int shmid;
    //******************第1步:创建共享内存**********************
    printf("共享内存大小： %d\n", sizeof(struct shared_use_st));//2048+4 = 2052
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1)// shmid和key_t没有关系
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    //******************第2步:将共享内存地址链接到本进程内存空间**********************
    //将共享内存映射到当前进程的地址空间
    origin_shm = shmat(shmid, (void *)0, 0);//第二个参数地址为0，表示自动分配地址
    if (origin_shm == (void *)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n", (int)origin_shm);//共享内存映射到本进程的起始地址
    shared = (struct shared_use_st *)origin_shm; //设置共享内存;结构体指向映射后的地址
    printf("shared:%#x\n", shared);
    //******************第3步:向共享内存写数据**********************
    while (running) //向共享内存中写数据
    {
        //非0可读,0可写;数据还没有被读取则等待数据被读取,不能向共享内存中写入文本
        while (shared->written == 1)//可读
        {
            sleep(1);
            printf("Waiting...\n");
        }
        printf("enter some text(end to stop): ");
        fgets(buffer, BUFSIZ, stdin);
        strncpy(shared->text, buffer, TEXT_SZ); //向共享内存中写入数据
        shared->written = 1;                    //写完数据，设置written使共享内存段可读
        if (strncmp(buffer, "end", 3) == 0)     //输入了end，退出循环（程序）
            running = 0;
    }
    if (shmdt(origin_shm) == -1) //把共享内存从当前进程中分离
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    exit(EXIT_SUCCESS);
}
