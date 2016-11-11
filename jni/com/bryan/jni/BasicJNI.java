package com.bryan.jni;

import java.util.Random;

/**
 * Author：Cxb on 2016/11/3 14:46
 */

public class BasicJNI {


    static {
        System.loadLibrary("jni");
    }


    public String name="hello";
    public static int age;

    public static void main(String[] args){
        BasicJNI jni=new BasicJNI();
        helloFromC();
    }

    public String getStr(String str){
        System.out.println(str);
        return  str+"_bibibi";
    }

    public static int getRandom(int rand){
        System.out.println(rand);
        return new Random().nextInt(rand);
    }

    //基本用法
    private static native String helloFromC();

    //用C拼接字符串
    private static native String concatStr(String str);

    //访问普通字段
    private native void accessField();
    //访问静态字段
    private native void accessStaticField();
   //访问普通方法
    private native void accessMethod();
    //访问静态方法
    private native void accessStaticMethod();

    //使用C语言创建一个Date对象，获取时间戳
    private native long accessConstructorMethod() ;
    //utf8转GBK
    private native String cTransformChar(String str) ;
    // 对数组进行排序
    private native void useArraySort(int[] array) ;
    // 在C中生存数组 ， 返回到Java中
    private native int[] getIntArray(int len) ;

    //局部引用 类似WeakReference
    private native void localRef();

    //全局引用
    private native void createGlobalRef();
    //释放全局引用
    private native void deleteGlobalRef();

}
