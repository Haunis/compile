/*
 *linux/unix: 管道是通过文件机制实现的
 *
 *本demo: 匿名管道在亲缘进程间的使用
 *参考:
 *	https://www.cnblogs.com/wuyepeng/p/9747557.html
 *	https://www.icourse163.org/learn/XIYOU-1461809182?tid=1470028455#/learn/content?type=detail&id=1252983749&sm=1
 *
 *管道通信流程:
 *	1.创建管道 pipe(int fd[2])
 *	2.关闭管道一端;根据需求选择关闭读端(close(fd[0]))还是写端(close(fd[1]))
 *	3.向管道写数据或者读取管道中的数据
 *
 *fork后,子进程持有和父进程同一个资源
 *所以主进程和子进程持有同一个管道的fd
 *一个进程关闭读fd[0],写数据;另一个进程关闭写fd[1],等待读数据;
 *这样两个有亲缘关系的进程就可以实现通信
 *
 * 管道机制必须提供以下几种能力：
 * 	1.互斥	读写必须互斥，一个进程对管道尽心读写操作时，另外一个进程必须等待
 * 	2.同步	写进程写入一定数量数据(如4KB)后，便要暂停写，等到读进程取走数据后，写进程才能继续写数据; 当读进程读到数据为空时，也要睡眠等待
 * 	3.确定对方是否存在
 * 	
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int t = 0;
	int x = t++; // 先将t赋值给x,再将t进程++动作--和本demo无关,只是一个小验证
	printf("x = %d, &x = %#x\n", x, &x);

	int fd[2]; // 文件描述符;0-读,1-写;
	// 1.创建管道;使用文件描述符指代管道
	int ret = pipe(fd);
	if (ret == -1)
	{
		printf("pipe error \n");
		return -1;
	}
	printf("***主进程 pid = %d\n", getpid());
	int pid = fork(); // 执行后父进程得到子进程pid,子进程得到0
	if (pid > 0)	  // 父进程,读
	{
		printf("***主进程 curpid = %d, pid=%d,fd[0]=%d, fd[1]=%d ,&fd=%#x\n", getpid(), pid, fd[0], fd[1], &fd);
		// 2.主进程关闭管道写端,保留读端
		close(fd[1]);
		int i = 0;
		while (i++ < 3)
		{
			char msg[100];
			memset(msg, '\0', sizeof(msg)); // 重置msg

			// 3.主进程从管道读消息
			printf("***主进程 receive ......\n");
			ssize_t s = read(fd[0], msg, sizeof(msg)); // 阻塞;如果写端关闭,则s=0
			if (s > 0)
			{
				msg[s - 1] = '\0';
			}
			printf("***主进程接收到: s=%d, msg=%s\n\n", (int)s, msg);
		}
	}
	else if (pid == 0) // 子进程,写
	{
		printf("---子进程x = %d, &x = %#x\n", x, &x);
		printf("---子进程 curpid = %d, pid=%d,fd[0]=%d, fd[1]=%d,&fd=%#x\n", getpid(), pid, fd[0], fd[1], &fd);
		// 4.子进程关闭读端,保留写端
		close(fd[0]);
		// char * msg = "abc_abc_abc"
		char msg[] = "abc_abc_abc";
		int i = 0;
		while (i++ < 3)
		{
			sleep(5);
			// 5.子进程向管道写数据
			// 读端一直不读数据,则写满阻塞,管道大小64k;读端关闭,进程收到SIGPIPE信号进程异常终止
			write(fd[1], msg, sizeof(msg));
		}
	}
	else
	{
		perror("fork error \n");
		return -1;
	}

	return 0;
}
