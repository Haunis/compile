/*
 *
 * 多生产者，多消费者，多个缓冲区
 * 一个生产者进程、一个消费者进程、多个缓冲区
 *
 * 参考：https://www.icourse163.org/learn/XIYOU-1461809182?tid=1470028455#/learn/content?type=detail&id=1252983747&sm=1
 *
 *
 *
 * 这里使用线程模拟进程
 *
 * 编译：
 *  g++ 04_mul_prod_con_cache_n.cpp -lpthread -o mul
 *
 *  在使用记录型信号量申请多种临界资源时，必须仔细分析，稍有不慎就会发生死锁
 *
 */

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep

#define PROD_NUM 8   // 生产者和消费者数量都是8
#define MAX_CACHE 10 // 缓冲区大小

void *producer(void *);
void *consumer(void *);

sem_t space;           // 信号量；缓冲区位置，开始为10
sem_t prod;            // 信号量；生产的产品，开始为0
sem_t buf;             // 信号量； 缓冲区本身也成为了临界资源，任何时候只有一个生产者或消费者进入缓冲区
int buffer[MAX_CACHE]; // 定义存储产品的数组buffer
int in = 0;            // 循环队列队尾指针，放产品
int out = 0;           // 循环队列队首指针，取产品

int main(void)
{
    sem_init(&space, 0, MAX_CACHE); // 第二个参数0表示只在本进程使用，大于0表示跨进程使用； 第三个参数表示初始值
    sem_init(&prod, 0, 0);
    sem_init(&buf, 0, 1); // 初始值为1，表示该缓冲区同时只能被一个进程访问

    pthread_t tid_p[PROD_NUM]; // 生产者线程
    pthread_t tid_c[PROD_NUM]; // 消费者线程

    // 开启多个生产者线程
    int prod_name[PROD_NUM];
    for (int i = 0; i < PROD_NUM; i++)
    {
        prod_name[i] = i + 1;
        pthread_create(&tid_p[i], NULL, producer, (void *)&prod_name[i]); //.cpp文件需要强转成void*; .c文件不需要
    }
    // 开启多个消费者线程
    int con_name[PROD_NUM];
    for (int i = 0; i < PROD_NUM; i++)
    {
        con_name[i] = i + 1;
        pthread_create(&tid_c[1], NULL, consumer, (void *)&con_name[i]);
    }
    sem_destroy(&space); // 释放信号量
    sem_destroy(&prod);

    pthread_join(tid_p[0], NULL); // 等待producer线程，否则主线程退出后，子线程也退出了

    printf("main thread exit ...\n");
    return 0;
}

// 一次最多可以放10个产品
void *producer(void *s)
{
    int prod_name = *((int *)s); // 第几个线程
    while (1)
    {
        sem_wait(&space); // 申请存储位置资源； space > 0 则获取锁，并将space -1;
        sem_wait(&buf);   // 获取缓冲区的控制权
        printf("%d put product buffer[%d]...\n", prod_name, in);
        in = (in + 1) % MAX_CACHE; // 将产品放在队尾位置，并修改队尾指针
        // sleep(1);
        sem_post(&buf);
        sem_post(&prod); // 释放prod锁，并将prod+1
    }
}

void *consumer(void *s)
{
    int con_name = *((int *)s); // 第几个线程
    while (1)
    {
        sem_wait(&prod); // 申请产品资源
        sem_wait(&buf);  // 申请获取buf产品控制权; 和上面的sem_wait(&prod)不能调换顺序，调换了则会和生产者线程发生死锁
        Swait();
        printf("%d get product buffer[%d] \n", con_name, out);
        out = (out + 1) % MAX_CACHE; // 从队头位置取产品，并修改队头指针
        // sleep(1);
        sem_post(&buf);
        sem_post(&space);
    }
}