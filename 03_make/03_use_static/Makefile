#不要这一行也行..
#main:math/libpower.a

main:main.o
#	g++ -o main main.o math/libpower.a	
	cmake -E cmake_link_script link.txt

clean:
	rm -rf main main.o
	@echo ""
	ls
.PHONY : clean
