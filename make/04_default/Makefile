#注意空行不能有table制表符

#就算伪目标也执行
.PHONY : all 
all:main.o add.o
	g++ -o main main.o add.o

#这两行可以都不要,make可以自行推导
main.o:main.cpp
#	g++ -c main.cpp

add.o:add.h

#add.o:add.cpp add.h
#	g++ -c add.cpp 

clean:
	-rm *.o main 
	tree
.PHONY : clean
