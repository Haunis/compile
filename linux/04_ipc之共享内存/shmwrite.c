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
    char buffer[BUFSIZ + 1];//用于保存输入的文本
    int shmid; 
	//******************第1步:创建共享内存**********************   
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
    if(shmid == -1)
    {  
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
	//******************第2步:将共享内存地址链接到本进程内存空间**********************   
	//将共享内存连接到当前进程的地址空间
    origin_shm = shmat(shmid, (void*)0, 0);   
    if(origin_shm == (void*)-1)
    {  
        fprintf(stderr, "shmat failed\n");     
        exit(EXIT_FAILURE);
    }  
    printf("Memory attached at %X\n", (int)origin_shm);   
    shared = (struct shared_use_st*)origin_shm;//设置共享内存   
	printf("shared:%#x\n",shared);	
	//******************第3步:向共享内存写数据**********************   
    while(running)//向共享内存中写数据  
    {   
		//非0可读,0可写;数据还没有被读取则等待数据被读取,不能向共享内存中写入文本       
        while(shared->written == 1)     
        {          
            sleep(1);      
            printf("Waiting...\n");
        }      
        printf("enter some text(end to stop): ");       
        fgets(buffer, BUFSIZ, stdin);      
        strncpy(shared->text, buffer, TEXT_SZ);//向共享内存中写入数据         
        shared->written = 1; //写完数据，设置written使共享内存段可读           
        if(strncmp(buffer, "end", 3) == 0)//输入了end，退出循环（程序）           
            running = 0;   
    }  
    if(shmdt(origin_shm) == -1)//把共享内存从当前进程中分离
    {      
        fprintf(stderr, "shmdt failed\n");     
        exit(EXIT_FAILURE);
    }  
    sleep(2);  
    exit(EXIT_SUCCESS);
}
