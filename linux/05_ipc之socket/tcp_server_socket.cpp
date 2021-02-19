#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h> //close函数在此文件定义

#define MAXLINE 4096

int main(int argc, char** argv)
{
    struct sockaddr_in     servaddr;
    char    buff[4096];
	//1.创建监听套接字
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd == -1)
	{
		printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
   		exit(0);
	}

	memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//本机任意一个ip
    servaddr.sin_port = htons(8888);
	//2.绑定端口
	int bind_ret = bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (bind_ret == -1)
	{
		printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	//3.设置监听,将套接字变为被动套接字
	int listen_ret = listen(listen_fd, 10) ;
	if (listen_ret == -1)
	{
		printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    	exit(0);
	}

	while (1)
	{
		//4.等待客户端链接
		printf("accept......\n");
		int conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);//阻塞
		if (conn_fd == -1)
		{
			printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
    	    continue;
		}
		while (1)
		{
			//5.使用服务套接字收发数据
			printf("recv......\n");
    		int n = recv(conn_fd, buff, MAXLINE, 0);//阻塞
    		buff[n] = '\0';
    		printf("recv msg size=%d, msg= %s\n",n, buff);
			if (n == 0)//客户端调用close或者客户端进程停止(ctrl+c)
			{ 
				printf("客户端调用close或停止运行 \n");
				close(conn_fd);
				break;
			}
		}
	}

	close(listen_fd);
}
