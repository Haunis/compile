
本demo演示的是java和c/c++互调，不涉及ndk相关内容


1.获取jni头文件
	javac com/jiage/Demo.java
	javah com.jiage.Demo


2.编译so库
	注意java版本是openjdk7
	编译c++文件成so库:
		gcc -shared -I /opt/java-7-openjdk-amd64/include -fPIC test.cpp -o libjni-test.so
	编译c文件成so库:
		gcc -shared -I /opt/java-7-openjdk-amd64/include -fPIC test.c -o libjni-test.so

3.运行java程序
	java -Djava.library.path=. com.jiage.Demo
	-Djava.library.path=. ：表示so库的路径


jni 头文件参数说明：
	JNIEnv *： 指向jni环境的指针，通过它可以访问jni提供的接口方法
	jobject: java对象中的this
	JNIEXPORT，JNICALL： jni定义的宏，可以再jni.h查找到


jni中，c和cpp代码区别：
c++: env->NewStringUTF(msg);
c  : (*env)->NewStringUTF(env,msg);


c/c++调用java方法流程：
	1. 通过类名找到类
		jclass clazz = env->FindClass("com/jiage/Demo");
	2.通过方法名和方法签名找到方法id
		jmethodID methodID = env->GetStaticMethodID(clazz, "func", "(Ljava/lang/String;)V");
	3.调用java里的方法
		env->CallStaticVoidMethod(clazz, methodID, msg);



签名：
	签名作用：c/c++代码里通过签名找到java类或者方法
	1.类的签名：
		采用"L+包名+类名+;"的形式，注意";"也是签名的一部分
	2.基本数据类型的签名
		boolean		Z	B已被byte占用，所以boolean签名是 Z
		byte		B
		char		C
		short		S
		int			I
		long		J	L已被类签名占用，所以用J
		float		F
		double		D
		void		V
	3.对象的签名
		就是对象所属类的签名
		如String	Ljava/lang/String;
	4.数组的签名
		int[]		[I
		float[]		[F
		double[]	[D
		long[]		[J
		String[]	[Ljava/lang/String;
		Object[]	[Ljava/lang/Object;
	5.多维数组的签名
		n个[+类型签名
		如int[][]	[[I
	6.方法的签名
		(参数类型签名)+返回值类型签名
		如： 
		boolean func(int a ,double,int[]c)		(ID[I)Z
		int func()								()I
		void func(int  i)						(I)V