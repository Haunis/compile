    /*使用消息队列通信*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
struct msg_st
{  
    long int msg_type; 
    char text[BUFSIZ];
};
int main()
{  
	printf("BUFSIZ = %d\n",BUFSIZ);//8192
	printf("IPC_CREAT= %d\n",IPC_CREAT);//512


    int running = 1;   
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 9999; //0--获取队列中第一个可用的消息;大于0则只能获取队列中相同类型的第一个消息
    //1.建立消息队列;
	//两个进程的消息队列持有相同的key才可以通信   
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT); 
    if(msgid == -1)
    {      
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);
    }  

	//2.从消息队列取消息
    while(running) 
    {  
		printf("msgrcv......\n");
		int ret = msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0);//阻塞;将收到的数据放在data中
        if(ret == -1)  
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE);    
        }  
        printf("rcv msg:  %s\n",data.text); 
        if(strncmp(data.text, "end", 3) == 0){ //遇到end结束       
            running = 0;   
		}
    }
	
	//3.删除消息队列   
    if(msgctl(msgid, IPC_RMID, 0) == -1)   
    {      
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);
    }  
    exit(EXIT_SUCCESS);
}
