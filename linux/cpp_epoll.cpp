/**
参考:https://blog.csdn.net/drdairen/article/details/53694550#commentBox

父进程和子进程使用pipe通信,父进程使用epoll监听读端等待子进程数据


epoll的使用:
	1.创建epoll,获取epoll fd
	2.使用epoll的fd注册想要的监听
	3.epoll_wait 等待监听的事件有变化(数据到来)
*/
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int main()
{
    struct epoll_event ev;//事件临时变量
    const int MAXEVENTS = 1024;//最大事件数
    struct epoll_event event_array[MAXEVENTS];//监听事件数组
    int ret,pid;
    int pipe_fd[2];
    if((ret=pipe(pipe_fd))<0)//创建管道的两端，0读 1写
    {
        cout<<"create pipe fail:"<<ret<< ",errno:" << errno <<endl;
        return -1;
    }
    ev.data.fd = pipe_fd[0];//设置监听文件描述符

    /*
	EPOLLLT:默认行为，基本上就是说,只要一个文件描述符处于就绪状态，epoll 就会不停的通知有事件发生。
	传统的 select/poll 都是这样的

	EPOLLET:是新的方式，只在一个文件描述符新处于就绪的时候通知一次，之后不管数据有没有读完，都不会再通知
	当然，有新数据到还是会通知的。
	所以，用 EPOLLET 的时候，一定要把文件描述符设置为 non-blocking，而且最好是一直读数据，读到返回 EAGAIN 才停下
	*/
    ev.events = EPOLLIN|EPOLLET; //设置要处理的事件类型

	//1.创建epoll
    int ep_fd=epoll_create(MAXEVENTS);
	//2.向epoll注册监听
    ret=epoll_ctl(ep_fd,EPOLL_CTL_ADD,pipe_fd[0],&ev);
    if (ret != 0)
    {
        cout << "epoll_ctl fail:" << ret << ",errno:" << errno << endl;
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(ep_fd);
        return -1;
    }
    if((pid=fork())>0)//父进程
    {
		printf("父进程 wait......\n");
		//3.epoll等待新事件到来;有新事件到来就解阻塞,并将事件保存到数组event_array中;
        int count=epoll_wait(ep_fd,event_array,MAXEVENTS,5000);//阻塞
		printf("父进程 新事件数量:%d\n",count);
        char r_buf[100];
        for(int i=0;i<count;i++)
        {
            if((event_array[i].data.fd==pipe_fd[0])&&(event_array[0].events&EPOLLIN))//监听的pipe字读端有新事件
            {
                int r_num=read(pipe_fd[0],r_buf,100);
                printf("父进程 读取字节数: %d bytes , value= %d \n",r_num,atoi(r_buf));
            }
        }
        close(pipe_fd[1]);
        close(pipe_fd[0]);
        close(ep_fd);
        cout<<"父进程 关闭 read fd[0],wirte fd[1] and ep_fd over"<<endl;

    }
    else if(pid==0)//子进程
    {
		sleep(5);
        close(pipe_fd[0]);//关读端
        char w_buf[100];
        strcpy(w_buf,"1234");
        if(write(pipe_fd[1],w_buf,5)!=-1)//子进程往管道里写
            printf("子进程 write over \n");
        close(pipe_fd[1]);//关写端
        printf("子进程 close write fd[1] over \n");
    }
    return 0;
}

