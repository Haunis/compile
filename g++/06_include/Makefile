main : main.o box.o cup.o
	g++ -o main main.o box.o cup.o

main.o : main.cpp
	g++ -c main.cpp

box.o : box.cpp box.h
	g++ -c box.cpp

cup.o: cup.cpp cup.h
	g++ -c cup.cpp

#伪目标,必须make clean 才能执行
#rm -f,-f 是强制删除的意思,不用提示
.PHONY : clean
clean:
	rm -f *.o main
 
