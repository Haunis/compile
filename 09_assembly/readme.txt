
c/c++源码编译成汇编代码:
	g++ -S main.cpp
	g++ -Og -S main.cpp # 使用符合原始C代码整体结构的机器代码优化等级



汇编操作码:
操作码	操作数	功能
mov		A,B		把B的值赋给A
and		A,B		A,B相加，结果赋给A
push	A		把A的值存储在栈中;	这里push、pop是对栈内存而言
pop		A		从栈中读出值，并赋值给A
call	A		调用函数A
ret		无		处理返回给调用函数  


