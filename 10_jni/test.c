#include "com_jiage_Demo.h"
#include <stdio.h>

void callJavaMethod(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL Java_com_jiage_Demo_set(JNIEnv *env, jobject thiz, jstring string)
{
	char *msg = (char *)(*env)->GetStringUTFChars(env, string, NULL);

	printf("c set invoke, msg=%s\n", msg);
	(*env)->ReleaseStringUTFChars(env, string, msg);
}

JNIEXPORT jstring JNICALL Java_com_jiage_Demo_get(JNIEnv *env, jobject thiz)
{
	callJavaMethod(env, thiz);

	char const *msg = "hello from c";
	printf("c get invoke, return: %s\n", msg);
	return (*env)->NewStringUTF(env, msg); //这个地方和cpp不同
}

void callJavaMethod(JNIEnv *env, jobject thiz)
{
	//1. 通过类名找到类
	jclass clazz = (*env)->FindClass(env, "com/jiage/Demo");
	if (clazz == NULL)
	{
		printf("error , no such class \n");
		return;
	}
	//2.通过方法名和方法签名找到方法id
	jmethodID methodID = (*env)->GetStaticMethodID(env, clazz, "func", "(Ljava/lang/String;)V");
	if (methodID == NULL)
	{
		printf("error , no such method \n");
		return;
	}
	//3.调用java里的方法
	jstring msg = (*env)->NewStringUTF(env, "hello from c");
	(*env)->CallStaticVoidMethod(env, clazz, methodID, msg);
}
