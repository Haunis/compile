/**
 * 创建线程，并打印用户线程对应的内核线程ktid
 *
 * 编译：
 *  gcc create_thread.c -lpthread -o main
 *
 */

#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define get_ktid() syscall(__NR_gettid) // 系统调用

void *printids(void *s)
{
    pid_t pid;
    pid_t ktid;
    pthread_t utid;

    pid = getpid();        // 当前进程
    utid = pthread_self(); // 用户级线程id
    ktid = get_ktid();       // 内核级线程id

    printf("%s pid= %u, utid= %u ,ktid= %u, (0x%x)\n",
           (char *)s, (unsigned int)pid, (unsigned int)utid, (unsigned int)ktid, (unsigned int)utid);

    // pause();
    sleep(2);
}

int main()
{
    pthread_t utid = 1; // 用户级线程utid， 值会改变
    pthread_create(&utid, NULL, printids, "new thread: ");

    printids("main thread: ");

    printf("main, utid=%u \n", (unsigned int)utid);

    sleep(1);

    return 0;
}
