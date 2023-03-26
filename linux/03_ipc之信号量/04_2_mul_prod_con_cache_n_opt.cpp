/*
 * 对多生产者、多消费者、多缓冲区问题优化
 * 不锁整个缓冲区，锁队头队尾。这样的话，同一时刻允许一个生产者线程、一个消费者线程同时访问
 *
 * 编译：
 *  g++ 04_2_mul_prod_con_cache_n_opt.cpp -lpthread -o mul
 */

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep

#define PROD_NUM 8   // 生产者和消费者数量都是8
#define MAX_CACHE 10 // 缓冲区大小

void *producer(void *);
void *consumer(void *);

sem_t space; // 信号量；缓冲区位置，开始为10
sem_t prod;  // 信号量；生产的产品，开始为0
sem_t sin;   // 信号量；队尾
sem_t sout;  // 信号量；队头

int buffer[MAX_CACHE]; // 定义存储产品的数组buffer
int in = 0;            // 循环队列队尾指针，放产品
int out = 0;           // 循环队列队首指针，取产品

int main(void)
{
    sem_init(&space, 0, MAX_CACHE); // 第二个参数0表示只在本进程使用，大于0表示跨进程使用； 第三个参数表示初始值
    sem_init(&prod, 0, 0);          // 初始值为0，开始没有产品
    sem_init(&sin, 0, 1);           // 初始值为1，同一时刻只能被一个生产者访问
    sem_init(&sout, 0, 1);          // 初始值为1，同一时刻只能被一个消费者访问

    pthread_t tid_p[PROD_NUM]; // 生产者线程id
    pthread_t tid_c[PROD_NUM]; // 消费者线程id

    int prod_name[PROD_NUM];
    for (int i = 0; i < PROD_NUM; i++) // 开启多个生产者线程
    {
        prod_name[i] = i + 1;
        pthread_create(&tid_p[i], NULL, producer, (void *)&prod_name[i]); //.cpp文件需要强转成void*; .c文件不需要
    }

    int con_name[PROD_NUM];
    for (int i = 0; i < PROD_NUM; i++) // 开启多个消费者线程
    {
        con_name[i] = i + 1;
        pthread_create(&tid_c[1], NULL, consumer, (void *)&con_name[i]);
    }
    sem_destroy(&space); // 释放信号量
    sem_destroy(&prod);
    sem_destroy(&sin);
    sem_destroy(&sout);

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
        sem_wait(&sin);   // 获取队尾控制权
        printf("%d put product buffer[%d]...\n", prod_name, in);
        in = (in + 1) % MAX_CACHE; // 将产品放在队尾位置，并修改队尾指针
        // sleep(1);
        sem_post(&sin);
        sem_post(&prod); // 释放prod锁，并将prod+1
    }
}

void *consumer(void *s)
{
    int con_name = *((int *)s); // 第几个线程
    while (1)
    {
        sem_wait(&prod); // 申请产品资源
        sem_wait(&sout); // 获取队头控制权
        printf("%d get product buffer[%d] \n", con_name, out);
        out = (out + 1) % MAX_CACHE; // 从队头位置取产品，并修改队头指针
        // sleep(1);
        sem_post(&sout);
        sem_post(&space);
    }
}