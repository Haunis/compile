/*
 *
 * 单生产者，单消费者问题
 * 一个生产者进程、一个消费者进程、一个一次只能放一个产品的缓冲区
 * 
 * 参考：https://www.icourse163.org/learn/XIYOU-1461809182?tid=1470028455#/learn/content?type=detail&id=1252983747&sm=1
 *
 *
 * 这里使用线程模拟进程
 *
 * 编译：
 *  g++ single_producer_consumer.cpp -lpthread -o single
 *
 */

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep

void *producer(void *);
void *consumer(void *);

sem_t space; // 缓冲区位置，开始为1
sem_t prod;  // 生产的产品，开始为0

int main(void)
{
    sem_init(&space, 0, 1); // 第二个参数0表示只在本进程使用，大于0表示跨进程使用； 第三个参数表示初始值
    sem_init(&prod, 0, 0);

    pthread_t tid[2];                                        // 保存线程id
    pthread_create(&tid[0], NULL, producer, (void *)"prod"); //.cpp文件需要强转成void*; .c文件不需要
    pthread_create(&tid[1], NULL, consumer, NULL);

    sem_destroy(&space); // 释放信号量
    sem_destroy(&prod);

    pthread_join(tid[0], NULL); //等待producer线程，否则主线程退出后，子线程也退出了

    printf("main thread exit ...\n");
    return 0;
}

void *producer(void *s)
{
    while (1)
    {
        sem_wait(&space); // space > 0则获取锁，并将space -1
        printf("put product ..\n");
        sleep(1);
        sem_post(&prod); // 释放prod锁，并将prod+1
    }
}

void *consumer(void *s)
{
    while (1)
    {
        sem_wait(&prod);
        printf("get product \n");
        sleep(1);
        sem_post(&space);
    }
}