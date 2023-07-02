/*
 * 参考:
 *	epoll: https://blog.csdn.net/drdairen/article/details/53694550#commentBox
 *  socket的send和write区别:https://www.cnblogs.com/kex1n/p/6501970.html
 * 
 * 编译:
 * 	g++ -o epoll tcp_epoll_server.cpp
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> //close函数在此文件定义
#include <sys/epoll.h>
#include <fcntl.h>
#include <iostream> //cout

#define MAXLINE 4096
using namespace std;

//设置socket连接为非阻塞模式
void setNonBlocking(int sockfd)
{
	int flags;
	flags = fcntl(sockfd, F_GETFL); // F_GETFL--获取fd标记
	if (flags < 0)
	{
		perror("fcntl(F_GETFL)\n");
		exit(1);
	}
	flags = (flags | O_NONBLOCK);
	if (fcntl(sockfd, F_SETFL, flags) < 0)
	{
		perror("fcntl(F_SETFL)\n");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	struct epoll_event ev;					   //事件临时变量
	const int MAXEVENTS = 1024;				   //最大事件数
	struct epoll_event event_array[MAXEVENTS]; //监听事件数组

	struct sockaddr_in servaddr;
	int n, nread;
	char buff[4096];
	char buf[BUFSIZ];
	cout << "EPOLLIN: " << EPOLLIN << endl;
	cout << "BUFSIZ: " << BUFSIZ << endl;
	// 1.创建监听套接字
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("listen_fd = %d\n", listen_fd);
	if (listen_fd == -1)
	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	setNonBlocking(listen_fd); //设置为非阻塞

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //本机任意一个ip
	servaddr.sin_port = htons(8888);
	// 2.绑定端口
	int bind_ret = bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (bind_ret == -1)
	{
		printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	// 3.设置监听,将套接字变为被动套接字
	int listen_ret = listen(listen_fd, 10);
	if (listen_ret == -1)
	{
		printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	// 4.1初始化epoll
	int ep_fd = epoll_create(MAXEVENTS);
	// 4.2向epoll注册监听
	ev.data.fd = listen_fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(ep_fd, EPOLL_CTL_ADD, listen_fd, &ev);
	if (ret != 0)
	{
		perror("epoll_ctl listen_fd error");
		exit(0);
	}

	// 3.处理epoll监听的回调
	for (;;)
	{
		printf("epoll_wait..........................\n");
		int count = epoll_wait(ep_fd, event_array, MAXEVENTS, -1); //-1永久阻塞;
		printf("epoll_wait,  count = %d\n", count);

		for (int i = 0; i < count; i++)
		{
			int fd = event_array[i].data.fd;
			printf("event_array[%d].fd = %d\n", i, fd);
			if (fd == listen_fd)
			{
				printf("监听套接字有变动，fd = %d\n",fd);
				int conn_fd;
				while ((conn_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL)) > 0)
				{
					printf("accept, conn_fd = %d\n", conn_fd);
					setNonBlocking(conn_fd);
					ev.data.fd = conn_fd;
					// ev.events = EPOLLIN;
					ev.events = EPOLLIN | EPOLLET;							 //边缘触发,非阻塞
					int ret = epoll_ctl(ep_fd, EPOLL_CTL_ADD, conn_fd, &ev); //监听conn_fd
					if (ret != 0)
					{
						perror("epoll_ctl conn_fd error");
						exit(0);
					}
				}
			}
			else
			{
				printf("服务套接字有变动，fd = %d\n",fd);
				if (event_array[i].events & EPOLLIN) //可读事件
				{
					// nread = read(fd, buf + n, BUFSIZ-1);
					// printf("nread = %d\n",nread);
					// while ( nread > 0)
					//{
					//	nread = read(fd, buf + n, BUFSIZ-1);
					//	printf("nread in = %d\n",nread);
					//     n += nread;
					// }
					// if (nread == -1 && errno != EAGAIN)
					//{
					//     perror("read error");
					// }
					// ev.data.fd = fd;
					// ev.events = event_array[i].events | EPOLLOUT;
					//修改该fd监听事件类型，监测是否可写
					// if (epoll_ctl(ep_fd, EPOLL_CTL_MOD, fd, &ev) == -1)
					//{
					//     perror("epoll_ctl: mod");
					// }

					// printf("recv......\n");
					int n = recv(fd, buff, MAXLINE, 0);
					buff[n] = '\0';
					printf("recv msg size=%d, msg= %s\n", n, buff);
					if (n == 0)
					{ //客户端调用close
						printf("客户端关闭!!!\n");
						close(fd);
						continue;
					}


					ev.data.fd = fd;
					ev.events = event_array[i].events | EPOLLOUT;
					//修改该fd监听事件类型，监测是否可写; 会触发一次EPOLLOUT事件
					if (epoll_ctl(ep_fd, EPOLL_CTL_MOD, fd, &ev) == -1)
					{
						perror("epoll_ctl: mod");
					}
				}

				if (event_array[i].events & EPOLLOUT) //可写事件
				{
					char msg[] = "Cpp Server Hello World";
					//字符串化命令
					sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s", strlen(msg), msg);
					int nwrite, data_size = strlen(buf);
					int n = data_size;
					while (n > 0)
					{
						nwrite = send(fd, buf + data_size - n, n, 0); //前三个参数和write一样,第四个参数是flag
						// nwrite = write(fd, buf + data_size - n, n);
						if (nwrite < n)
						{
							if (nwrite == -1 && errno != EAGAIN)
							{
								perror("write error");
							}
							break;
						}
						n -= nwrite;
					}
					//写完就关闭该连接socket
					// close(fd);
					printf("write executed \n");
					usleep(1 * 1000 * 1000);


					ev.data.fd = fd;
					ev.events = EPOLLIN;
					//修改该fd监听事件类型，监测是否可读; 不会触发一次EPOLLIN事件
					if (epoll_ctl(ep_fd, EPOLL_CTL_MOD, fd, &ev) == -1)
					{
						perror("epoll_ctl: mod");
					}
				}
			}
		}
	}

	close(listen_fd);
}
