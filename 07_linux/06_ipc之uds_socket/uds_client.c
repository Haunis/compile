/**
 *
 * 编译： gcc -o client uds_client.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stddef.h> //offsetof宏的头文件

#define UDS_PATH "uds_test"
int main(voi)
{
    struct sockaddr_un addr_srv;
    char buf[100];
    memset(buf, 0, sizeof(char) * 100);
    strcpy(buf, "msg from client");

    //1.创建套接字
    int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        return -1;
    }

    addr_srv.sun_family = AF_UNIX;
    strcpy(addr_srv.sun_path, UDS_PATH);
    int addr_size = offsetof(struct sockaddr_un, sun_path) + strlen(addr_srv.sun_path);

    //2.连接服务端
    int conn_ret = connect(socket_fd, (struct sockaddr *)&addr_srv, addr_size);
    if (conn_ret < 0)
    {
        return -1;
    }

    int send_ret = send(socket_fd, buf, strlen(buf), 0);
    if (send_ret < 0)
    {
        return -1;
    }

    int data_len = recv(socket_fd, buf, 100, 0);//阻塞
    if (data_len > 0)
    {
        buf[data_len] = '\0';
        printf("msg from server: %s\n", buf);
    }
    else
    {
        printf("close ...\n");
        close(socket_fd);
        return -1;
    }

    close(socket_fd);
    return 0;
}