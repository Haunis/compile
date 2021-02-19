参考:https://www.cnblogs.com/wuyepeng/p/9747515.html
	https://www.cnblogs.com/wuyepeng/p/9747557.html

特点:
	面向字节流
	管道随进程,进程在管道在;进程消失,管道对应的端口也关闭

匿名管道:
	1.半双工,数据只能单向流动,就像对讲机一样,同一时刻只能有一个写一个读
	2.只能在有亲缘关系的进程间进行通信(如fork出的进程)

流管道 s_pipe:
	去除了第一条限制,可以双向传输

命名管道 name_pipe:
	可以双向传输,允许无亲缘关系的进程间通信
