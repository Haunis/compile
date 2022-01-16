package com.jiage;

public class Demo {
    static {
        System.loadLibrary("jni-test");
    }

    public static void main(String[] args) {
        Demo d = new Demo();

        String msg = "hello from java";
        System.out.println("java set(), msg=" + msg);
        d.set(msg);

        String ret = d.get();
        System.out.println("java get(), ret=" + ret);
    }

    public static void func(String msg) { // jni调用该方法
        System.out.println("java func called...., msg=" + msg);
    }

    public native void set(String arg);

    public native String get();
}
