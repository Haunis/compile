#在linux下cc就是指向了gcc; c++指向g++

#文件中第一个target作为最终目标
edit:main.o
#	cc -o main main.o
	g++ -o main main.o
	@echo "........"

main.o:main.cpp
#	cc -c main.cpp
	g++ -c main.cpp

clean:
	rm main.o main
