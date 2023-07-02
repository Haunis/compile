//头文件一般定义 函数声明，变量声明，宏声明，结构体声明
//如果定义了具体的函数了，在多个目标文件(linux中是.o)文件链接时会报错
int add(int x,int y);

extern int cout ; 
