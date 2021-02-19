#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>
#define MAX_TEXT 512
struct msg_st
{  
    long int msg_type; 
    char text[MAX_TEXT];
};
int main()
{  
	printf("MAX_TEXT: %d\n",MAX_TEXT);	


    int running = 1;   
    struct msg_st data;
    char buffer[BUFSIZ];//8192
    int msgid = -1;     

	//1.建立消息队列
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);//阻塞
    if(msgid == -1)
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);
    }
	  
	//2.向消息队列中写消息
    while(running) 
    {       
        printf("enter some text(end--exit): "); //输入数据   
        fgets(buffer, BUFSIZ, stdin);  
        data.msg_type = 9999;    //消息类型;接收端只有设置相同的类型或者0方可接收;接收端设置成0可接收队列中第一个数据   
        strcpy(data.text, buffer);  
   
		//向队列发送数据  
        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1) 
        {      
            fprintf(stderr, "msgsnd failed\n");    
            exit(EXIT_FAILURE);    
        }       
		//输入end结束输入    
        if(strncmp(buffer, "end", 3) == 0)     
            running = 0;   
        sleep(1);
    }  
    exit(EXIT_SUCCESS);
}
