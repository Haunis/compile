linux进程间通信之消息队列
参考:https://www.cnblogs.com/wuyepeng/p/9748728.html
感觉跟python中进程间通信queue差不多

和命名管道相同的地方:
	1.和管道一样都对数据有最大长度限制
	2.利用消息队列和管道通信的进程可以是不相干的进程
	3.都是一个发送端一个接收端
和命名管道不同的地方:
	1.消息队列可独立发送和接收进程而存在,从而消除了在同步命名管道的打开和关闭时可能产生的困难(不明白)
	2.同时通过发送消息还可以避免命名管道的同步和阻塞问题，不需要由进程自己来提供同步方法(不明白)
	3.接收程序可以通过消息类型有选择地接收数据，而不是像命名管道中那样，只能默认地接收。

接收
	1.建立消息队列:
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT); 
	2.接收数据
	msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0);//返回-1则失败
	该方法阻塞

发送
	1.建立消息队列:
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	2.向队列写数据
	msgsnd(msgid, (void*)&data, MAX_TEXT, 0);//返回-1则失败
	data是个结构体,里面包含消息类型和消息内容	
