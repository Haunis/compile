/*
 * UDS: unix domain socket
 *      是专门针对单机的进程间通信提出来的，和Net Socket虽然用法上相似，但在实现原理上有很大区别
 *      Net Socket是以TCP/IP协议为基础的，需要分包、重组等一系列操作。
 *      而UDS因为是本机内的“安全可靠操作”，实现机制上并不依赖于这些协议
 *
 * 编译：
 *      gcc -o server uds_server.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h> //socket头文件
#include <sys/un.h>
#include <sys/types.h>
#include <stddef.h> //offsetof宏的头文件

#define UDS_PATH "uds_test"
#define MAXLINE 1000

int main(void)
{
    struct sockaddr_un server_addr, client_addr;
    char buf[100]; //用于通信
    memset(buf, 0, sizeof(buf));

    // 1.创建监听套接字
    int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_fd < 0)
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, UDS_PATH); //设置path name
    // offsetof:结构体成员sun_path在sockaddr_un中的偏移量
    int addr_size = offsetof(struct sockaddr_un, sun_path) + strlen(server_addr.sun_path);
    // 2.绑定端口
    int ret = bind(listen_fd, (struct sockaddr *)&server_addr, addr_size);
    if (ret < 0)
    {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    // 3.设置监听,将套接字变为被动套接字
    int listen_ret = listen(listen_fd, 10);
    if (listen_ret < 0)
    {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }

    while (1)
    {
        int sz = sizeof(client_addr);

        // 4.等待客户端链接
        printf("accept......\n");
        int conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &sz);
        if (conn_fd == -1)
        {
            printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
            continue;
        }

        while (1)
        {
            // 5.使用服务套接字收发数据
            printf("recv......\n");
            int data_len = recv(conn_fd, buf, MAXLINE, 0); //阻塞
            if (data_len <= 0)                             //客户端调用close或者客户端进程停止(ctrl+c)
            {
                printf("客户端调用close或停止运行 \n");
                close(conn_fd);
                break;
            }
            else
            {
                buf[data_len] = '\0';
                printf("recv buf size=%d, buf= %s\n", data_len, buf);
            }

            strcpy(buf, "msg from server...");
            int send_ret = send(conn_fd, buf, strlen(buf), 0);
            if (send_ret < 0)
            {
                close(conn_fd);
                break;
            }
        }
        close(conn_fd);
    }

    close(listen_fd);
    return 0;
}