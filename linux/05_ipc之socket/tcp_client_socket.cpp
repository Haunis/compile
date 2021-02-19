/*
编译: g++ -o client tcp_client_socket.cpp -lpthread

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>//strlen
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h> //close()在该文件定义
#include<pthread.h>

#define MAXLINE 4096

void* recv_msg(void* arg){
	int sock_fd = *((int*)arg);
	printf("recv_msg arg=%#x,sock_fd=%d\n",arg,sock_fd);

	while(1){
		char buff[4096];
		printf("recv................\n");
		int n = recv(sock_fd, buff, MAXLINE, 0);//阻塞
    	buff[n] = '\0';
    	printf("recv msg size=%d, msg= %s\n",n, buff);
    	if(n==0){//服务端调用了close
		    close(sock_fd);
			exit(0);
    	}
	}
}

int main(int argc, char** argv)
{
    char recvline[4096], sendline[4096],ip_address[10];
    struct sockaddr_in server_address;
	pthread_t tid;

	//1.创建套接字,得到fd; SOCK_STREAM是tcp连接
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( sock_fd < 0){
   		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    	exit(0);
    }

	//2.链接服务器
	printf("请输入ip:");
	scanf("%s",&ip_address);
	printf("ip_addr=%s\n",ip_address);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);

    if( inet_pton(AF_INET, ip_address, &server_address.sin_addr) <= 0){//将“点分十进制” －> “二进制整数”
   		 printf("inet_pton error for %s\n",argv[1]);
   		 exit(0);
    }
	//server_address.sin_addr.s_addr = inet_addr(ip_address);//或者该方式转换
		
	int connect_ret = connect(sock_fd, (struct sockaddr*)&server_address, sizeof(server_address));//链接服务器
    if(connect_ret< 0){
    	printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    	exit(0);
    }

	//3.子线程接收数据	
	printf("main &sock_fd=%#x,sock_fd=%d\n",&sock_fd,sock_fd);
	int thread_ret = pthread_create(&tid,NULL,recv_msg,(void*)&sock_fd);	
	if(thread_ret!=0){
		perror("create thread filed");
		exit(0);
	}
	sleep(1);//为了打印美观,让子线程线先执行

	//3.主线程发送数据
	while(1){
    	printf("send msg to server(quit-结束):\n");
    	//fgets(sendline, 4096, stdin);
		scanf("%s",&sendline);
		if(strcmp("quit",sendline)==0){
			close(sock_fd);
			exit(0);
		}else{
			int send_ret = send(sock_fd, sendline, strlen(sendline), 0);
    		if(  send_ret < 0)
    		{
    			printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
    			exit(0);
    		}
		}
	}

}
