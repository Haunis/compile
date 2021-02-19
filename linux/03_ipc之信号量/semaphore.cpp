/*
编译: g++ -o sema semaphore.cpp -lpthread

参考:https://www.cnblogs.com/wuyepeng/p/9748552.html
	https://blog.csdn.net/gatieme/article/details/50994533

信号量一般作为同步手段使用,而不作为进程间通信媒介

信号量的分类:
	1.内核信号量;由内核控制路径使用,只能在内核使用,是一种睡眠所
	2.用户态进程使用的信号量:POSIX信号量和SYSTEM V信号量
信号量只能进行两种操作:
	1.P(sv):如果sv的值大于0,就将值减1;等于0,则挂起等待(申请资源)
	2.V(sv):如果有其他进程因等待sv而挂起,就让该进程恢复;否则将sv值加1(释放资源)

本例使用的是POSIX信号量中的无名信号量
无名信号量主要用于同一进程多线程同步,或亲缘进程同步(fork出的)

*/
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define total 20
sem_t remain, apple, pear, mutex;//创建信号量
static unsigned int vremain = 20, vapple = 0, vpear = 0;
void *father(void *);
void *mather(void *);
void *son(void *);
void *daughter(void *);
void print_sem();
int main()
{  
    pthread_t t_fa,t_ma, t_so, t_da;  

	//第一个参数remain是无名信号量
	//第二个参数等于0用于同一进程多线程间同步;大于0用于多进程间同步(fork产生)
	//第三个参数是信号量初始值
    sem_init(&remain, 0, total);//总数初始化为20 
    sem_init(&apple, 0, 0);//盆子中苹果数, 开始为0  
    sem_init(&pear, 0, 0);//盆子中梨子数, 开始为0   
    sem_init(&mutex, 0, 1);//互斥锁, 初始为1 
    pthread_create(&t_fa, NULL, &father, NULL);  
    pthread_create(&t_ma, NULL, &mather, NULL);  
    pthread_create(&t_so, NULL, &son, NULL); 
    pthread_create(&t_da, NULL, &daughter, NULL);    
    for(;;);
}

//remain -1,一直放苹果
void *father(void *arg)
{  
    while(1)
    { 
		//相当于P操作,即申请资源 
		//阻塞;remain>0 ,减1并立即返回;remain==0,睡眠到remain>0     
        sem_wait(&remain);
        sem_wait(&mutex);      
        printf("父亲: 放苹果之前, 剩余空间=%u, 苹果数=%u\n", vremain--, vapple++);
        printf("父亲: 放苹果之后, 剩余空间=%u, 苹果数=%u\n", vremain, vapple);

		//相当于V操作,即释放资源;将指定的信号量mutex+1,唤醒正在等待该信号量的任意线程
        sem_post(&mutex);      
        sem_post(&apple);  
        sleep(1);  
    }
}

//remain -1,一直放梨
void *mather(void *arg)
{  
    while(1)
    {      
        sem_wait(&remain);     
        sem_wait(&mutex);      
        printf("母亲: 放梨子之前, 剩余空间=%u, 梨子数=%u\n", vremain--, vpear++);
        printf("母亲: 放梨子之后, 剩余空间=%u, 梨子数=%u\n", vremain, vpear);
        sem_post(&mutex);  
        sem_post(&pear);   
        sleep(2);  
    }
}

//remain +1,一直吃苹果
void *son(void *arg)
{  
    while(1)
    {      
        sem_wait(&apple);//初始值0,挂起等待   
        sem_wait(&mutex);   
        printf("儿子: 吃苹果之前, 剩余空间=%u, vapple=%u\n", vremain++, vapple--);
        printf("儿子: 吃苹果之后, 剩余空间=%u, vapple=%u\n", vremain, vapple);
        sem_post(&mutex);  
        sem_post(&remain);     
        sleep(3);
    }
}

//remian +1,一直吃梨
void *daughter(void *arg)
{  
    while(1)
    {  
        sem_wait(&pear);//初始值0,挂起等待  
        sem_wait(&mutex);
        printf("女儿: 吃梨之前, 剩余空间=%u, vpear=%u\n", vremain++, vpear--);
        printf("女儿: 吃梨之前, 剩余空间=%u, vpear=%u\n", vremain, vpear);   
        sem_post(&mutex);  
        sem_post(&remain); 
        sleep(3);  
    }
}
void print_sem()
{  
    int val1, val2, val3;
	//取信号量remain当前值,并保存在vall中	
    sem_getvalue(&remain, &val1);  
    sem_getvalue(&apple, &val2);   
    sem_getvalue(&pear, &val3);
    printf("Semaphore: remain:%d, apple:%d, pear:%d\n", val1, val2, val3);
}
