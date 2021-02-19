link_libraries和target_link_libraries区别:
https://blog.csdn.net/harryhare/article/details/89143410
https://blog.csdn.net/jigetage/article/details/84206082
	1.link_libraries用在add_executable之前
	  target_link_libraries用在add_executable之后


	2.link_libraries用来链接静态库
	  target_link_libraries用来链接导入库
	  即按照header file + .lib + .dll方式隐式调用动态库的.lib库




cmake 生成Makefile,执行make后的调用链:
(以04_gen_static为例说明)
	1.Makefile: 
		-->default_target: all
		-->all:cmake_check_build_system
			 $(MAKE) -f CMakeFiles/Makefile2 all
	2.CMakeFiles/Makefile2: 
		   all: CMakeFiles/main.dir/all
		   all: math/all
		-->CMakeFiles/main.dir/all: math/CMakeFiles/Power.dir/all (所以会先编译power....)
			$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/depend
			$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
				
			-->	math/CMakeFiles/Power.dir/all:(先编译生成libpower.a)
					$(MAKE) -f math/CMakeFiles/Power.dir/build.make math/CMakeFiles/Power.dir/depend
					$(MAKE) -f math/CMakeFiles/Power.dir/build.make math/CMakeFiles/Power.dir/build	
		-->math/all: math/CMakeFiles/Power.dir/all
			math/CMakeFiles/Power.dir/all:
			$(MAKE) -f math/CMakeFiles/Power.dir/build.make math/CMakeFiles/Power.dir/depend
			$(MAKE) -f math/CMakeFiles/Power.dir/build.make math/CMakeFiles/Power.dir/build 

	3.math/CMakeFiles/Power.dir/build.make 
		math/CMakeFiles/Power.dir/build: math/libPower.a

	4.CMakeFiles/main.dir/build.make 
		-->CMakeFiles/main.dir/build: main
		-->	main: CMakeFiles/main.dir/build.make
			main: CMakeFiles/main.dir/main.cpp.o
			main: math/libPower.a
	
