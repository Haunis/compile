#main是最终的目标文件
main:main.o
#可以不要该行指令,make可以自行推导
	g++ -o main main.o

#command可以不用写,make可以自动推导
main.o:main.cpp
#	cc -c main.cpp


#rm前"-"的意思是如果清除失败,则继续进行
#如果当前目录有和该伪目标重名的文件,伪目标下面的command依然执行
#如果目标文件冒号后面啥也没有,make就不会去寻找文件的依赖性,也不会自动执行其后定义的指令
#要想执行其后指令必须显示调用,如 make clean
#.PHONY 显示指明clean是伪目标，不管是否有clean这个文件，clean这个目标就是个伪目标

.PHONY : clean
clean: #clean后面啥也没,make不会寻找文件的依赖性,不会自动执行其后定义的指令
	-rm main.o main

#.PHONY : clean     #.PHONY 也可以放在目标文件的后面
