定制安装规则和测试

1.定制安装规则
	a.在要生成静态库的目录math下，修改CMakeLists.txt
		install(TARGETS Power DESTINATION bin)
		install(FILES power.h DESTINATION include)
	b.修改根目录CMakeLists.txt
		install(TARGETS main DESTINATION bin)
		install(FILES "${PROJECT_SRC_DIR}/config.h" include)
	
	通过此两步设置libPower.a库和main可执行文件将被拷贝到/usr/bin;power.h和config.h将被拷贝至/usr/bin/include
	/usr/local/是默认安装到根目录，可通过修改CMAKE_INSTALL_PREFIX
	变量的值，来指定这些文件安装到哪里

	<<<<<<在build目录执行sudo make install,即可安装>>>>>>
	
2.为工程增加测试
	enable_testing()#启用测试
	add_test(test_run main 5 2)#测试程序是否成功运行
	
	#测试帮助信息是否可以正常显示
	add_test(test_usage main)
	set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "argv*")
	
	add_test(test_5_2 main 5 2)#测试5的平方
	set_tests_properties(test_usage PROPERTIES PASS_REGULAR_EXPRESSION "= 25")#注意要和main.cpp最后输出的格式要一致
	
	
	#一个一个写太麻烦，可以定义一个宏来简化测试
	macro(do_test arg1 arg2 result)
		add_test(test_${arg1}_${arg2} main ${arg1} ${arg2})
		set_tests_properties(test_${arg1}_${arg2} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
	endmacro (do_test)

	do_test(2 2 "= 4") 
	do_test(2 3 "= 8") 

	<<<<<在build执行make test即可运行测试>>>>>	

3.支持gdb
	set(CMAKE_BUILD_TYPE "Debug")
	set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
