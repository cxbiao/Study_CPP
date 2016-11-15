package com.bryan.jni;

import java.util.Random;

import javax.print.attribute.standard.MediaSize;

/**
 * Author：Cxb on 2016/11/3 14:46
 */

public class BasicJNI {


    static {
        System.loadLibrary("jni");
    }


    //私有字段也可以JNI调用
    private String name="hello";
    private static int age;

    public static void main(String[] args){
        BasicJNI jni=new BasicJNI();
        System.out.println(helloFromC());
        System.out.println("======================");
        System.out.println(concatStr("who he is"));
        System.out.println("======================");
        System.out.println("old name:"+jni.name);
        jni.accessField();
        System.out.println("new name:"+jni.name);
        System.out.println("======================");
        System.out.println("old age:"+age);
        jni.accessStaticField();
        System.out.println("new age:"+age);
        System.out.println("======================");
        jni.accessMethod();
        System.out.println("======================");
        jni.accessStaticMethod();
        System.out.println("======================");
        System.out.println(jni.accessConstructorMethod());
        System.out.println("======================");
        System.out.println(jni.cTransformChar("hello诛仙===="));
        System.out.println("======================");
        int[] iarr={21,-8,25,211,1,541};
        jni.useArraySort(iarr);
        for(int i=0;i<iarr.length;i++){
            System.out.println("int array:"+iarr[i]);
        }
        System.out.println("======================");
        int[] temp=jni.getIntArray(5);
        for(int i=0;i<temp.length;i++){
            System.out.println("C make array:"+temp[i]);
        }
        System.out.println("======================");
        jni.localRef();
        System.out.println("======================");
        jni.createGlobalRef();
        System.out.println("======================");
        System.out.println("GlobalRef:"+jni.useGlobalRef());
        System.out.println("======================");
        jni.deleteGlobalRef();
        System.out.println("======================");
    }

    //私有方法也可以JNI调用
    private String getStr(String str){
        System.out.println(str);
        return  str+"_bibibi";
    }

    private static int getRandom(int rand){
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
    private native String useGlobalRef();
    //释放全局引用
    private native void deleteGlobalRef();

}
