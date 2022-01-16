#include "com_jiage_Demo.h"
#include <stdio.h>

/**
 * 
 * @param env 指向jni环境的指针，通过它可以访问jni提供的接口方法
 * @param thiz  java对象中的this
 * @param string 
 * 	
 * JNIEXPORT，JNICALL： jni定义的宏，可以再jni.h查找到
 */
void callJavaMethod(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL Java_com_jiage_Demo_set(JNIEnv *env, jobject thiz, jstring string)
{
	char *ret = (char *)env->GetStringUTFChars(string, NULL);

	printf("c++ set invoke, ret=%s\n", ret);
	env->ReleaseStringUTFChars(string, ret);
}

JNIEXPORT jstring JNICALL Java_com_jiage_Demo_get(JNIEnv *env, jobject thiz)
{
	callJavaMethod(env, thiz);

	char const *msg = "hello from c++";
	printf("c++ get invoke, return: %s\n", msg);
	return env->NewStringUTF(msg);
}

//调用java代码
void callJavaMethod(JNIEnv *env, jobject thiz)
{
	//1. 通过类名找到类
	jclass clazz = env->FindClass("com/jiage/Demo");
	if (clazz == NULL)
	{
		printf("error , no such class \n");
		return;
	}
	//2.通过方法名和方法签名找到方法id
	jmethodID methodID = env->GetStaticMethodID(clazz, "func", "(Ljava/lang/String;)V");
	if (methodID == NULL)
	{
		printf("error , no such method \n");
		return;
	}
	//3.调用java里的方法
	jstring msg = env->NewStringUTF("hello from c++");
	env->CallStaticVoidMethod(clazz, methodID, msg);
}
