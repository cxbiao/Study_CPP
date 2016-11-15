#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "com_bryan_jni_BasicJNI.h"


JNIEXPORT jstring JNICALL Java_com_bryan_jni_BasicJNI_helloFromC(JNIEnv *env, jclass clazz){

    return env->NewStringUTF("hello world from C");

}

JNIEXPORT jstring JNICALL Java_com_bryan_jni_BasicJNI_concatStr(JNIEnv *env, jclass clazz, jstring jstr){

   const char *str=env->GetStringUTFChars(jstr,JNI_FALSE);
   char ret[100];
   strcpy(ret,str);
   strcat(ret,"_concatstr");
   env->ReleaseStringUTFChars(jstr,str);
   printf("C print %s--\n",ret);
   return env->NewStringUTF(ret);

}

/**

  编写套路
   C语言访问Java语言的字段与方法 ， 只要理解了一种 ， 其他的都是套路 ， 根据步骤一步一步来就可以了 。
   步骤一 、 得到jclass ， 字节码对象 ， 如果是static native修饰 ， 则函数会以jclass类型传入 ， 非静态则需要得到jclass类型 。

   // 得到jclass
    jclass jclazz = (*env)->GetObjectClass(env, jobj);

   步骤二 、得到字段或方法ID , 区分静态字段与对象字段 ， 静态字段或方法调用(*env)->GetStaticFieldID得到静态字段ID ，(*env)->GetStaticMethodID得到静态方法ID ，
   对象字段调用(*env)->GetFieldID得到字段ID，(*env)->GetMethodID得到方法ID 。 可以得到一个套路 ， 静态修饰的 ， 则调用static标识的函数 ， 非静态的则调用常规函数 。

  // 得到字段ID ， 对象字段
   jfieldID jfid = (*env)->GetFieldID(env, jclazz, "age", "I");

  // 得到字段ID ， 静态字段
  jfieldID jfid = (*env)->GetStaticFieldID(env, jclazz, "flag", "Ljava/lang/String;");

  步骤三 、 取得字段的值或调用方法 , 需要注意的是， 得到字段的值与调用方法 ， 都有类型的区分 。引用类型则使用GetObjectField ， CallStaticObjectMethod ，
  其他类型 ， 则有对于的jxxx类型对应 。套路简写：Get<Type>Field ， GetStatic<Type>Field ， Call<Type>Method ， CallStatic<Type>Method 。

  步骤四 、 类型转换 ， 如果是Java引用类型 ， 则需要进行类型转换

  // 将java字符串转换成字符指针
   char* cflag = (*env)->GetStringUTFChars(env, jflag, JNI_FALSE);


*/

JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_accessField(JNIEnv *env, jobject jobj){


    //获得对象所对应的类
    jclass clazz=env->GetObjectClass(jobj);
    //得到fieldId
    jfieldID fid=env->GetFieldID(clazz,"name","Ljava/lang/String;");
    if(fid==NULL){
        printf("wrong field name\n");
        return;
    }
    //得到field的值
    jstring str=(jstring)env->GetObjectField(jobj,fid);
    const char * cstr=env->GetStringUTFChars(str,JNI_FALSE);
    printf("C print old name=%s--\n",cstr);
    env->ReleaseStringUTFChars(str,cstr);
    const char *newname="mike中";
    jstring jnewname=env->NewStringUTF(newname);
    //设置field的值
    env->SetObjectField(jobj,fid,jnewname);
    printf("C print new name=%s--\n",newname);

}


JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_accessStaticField(JNIEnv *env, jobject jobj){

    jclass clazz=env->GetObjectClass(jobj);
    //取出静态字段fieldId
    jfieldID fid=env->GetStaticFieldID(clazz,"age","I");
     if(fid==NULL){
        printf("wrong field age\n");
        return;
    }
    //得到静态字段值
    jint age=env->GetStaticIntField(clazz,fid);
    printf("C print old age %ld--\n",age);
    jint newage=age+10;
     //设置静态field的值
    env->SetStaticIntField(clazz,fid,newage);
    printf("C print new age %ld--\n",newage);
}


JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_accessMethod(JNIEnv *env, jobject jobj){
    jclass clazz=env->GetObjectClass(jobj);
    //得到方法id
    jmethodID mid=env->GetMethodID(clazz,"getStr","(Ljava/lang/String;)Ljava/lang/String;");
    if(mid==NULL){
        printf("wrong method getStr\n");
        return;
    }
    //调用方法
    jstring ret=(jstring)env->CallObjectMethod(jobj,mid,env->NewStringUTF("taobao"));
    const char *cstr=env->GetStringUTFChars(ret,JNI_FALSE);
    printf("C result %s--\n",cstr);
    env->ReleaseStringUTFChars(ret,cstr);

}


JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_accessStaticMethod(JNIEnv *env, jobject jobj){
    jclass clazz=env->GetObjectClass(jobj);
     //得到静态方法id
    jmethodID mid=env->GetStaticMethodID(clazz,"getRandom","(I)I");
    if(mid==NULL){
        printf("wrong method getRandom\n");
        return;
    }
    //调用静态方法
    jint ret=env->CallStaticIntMethod(clazz,mid,100);
    printf("C result %ld--\n",ret);
}


JNIEXPORT jlong JNICALL Java_com_bryan_jni_BasicJNI_accessConstructorMethod(JNIEnv *env, jobject jobj){
    jclass clazz=env->FindClass("java/util/Date");
    //得到构造方法<init>
    jmethodID mid=env->GetMethodID(clazz,"<init>","()V");
    //生成一个新对象
    jobject obj=env->NewObject(clazz,mid);
    jmethodID timeMid=env->GetMethodID(clazz,"getTime","()J");
    jlong time=env->CallLongMethod(obj,timeMid);
    printf("C current timestamp %lld---\n",time);
    return time;


}

//utf8--gbk
JNIEXPORT jstring JNICALL Java_com_bryan_jni_BasicJNI_cTransformChar(JNIEnv *env, jobject jobj, jstring jstr){
   jclass clazz=env->GetObjectClass(jstr);
   jmethodID mid=env->GetMethodID(clazz,"getBytes","(Ljava/lang/String;)[B");
   jstring gbk=env->NewStringUTF("GBK");
   jbyteArray bytes=(jbyteArray)env->CallObjectMethod(jstr,mid,gbk);
   jsize len=env->GetArrayLength(bytes);
   jbyte buf[len];
   env->GetByteArrayRegion(bytes,0,len,buf);

   jmethodID midInit=env->GetMethodID(clazz,"<init>","([BLjava/lang/String;)V");
   jstring ret=(jstring)env->NewObject(clazz,midInit,bytes,gbk);

    const char*str=env->GetStringUTFChars(ret,JNI_FALSE);
    printf("C gbk string %s\n",str);
    FILE *file=fopen("test.txt","w");
    fputs(str,file);
    fclose(file);
    env->ReleaseStringUTFChars(ret,str);
    return ret;


}

int compare_int(const void* a, const void* b){

    const int *arg1 = (const int *)a;
    const int *arg2 = (const int *)b;
    return *arg1 - *arg2;
}


JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_useArraySort(JNIEnv *env, jobject jobj, jintArray arr){
    jsize len=env->GetArrayLength(arr);
    jint *parr=env->GetIntArrayElements(arr,JNI_FALSE);
    qsort(parr,len,sizeof(int),compare_int);
    // 释放引用 ， 因为数组和对象在java中都是引用 ， 都会在堆内存中开辟一块空间 ， 但我们使用完对象之后
    // 需要将引用释放掉 ， 不然会很耗内存 ， 在一定程度上可能会造成内存溢出 。
    //JNI_ABORT, Java数组不进行更新，但是释放C/C++数组
    //JNI_COMMIT，Java数组进行更新，不释放C/C++数组（函数执行完，数组还是会释放）
    env->ReleaseIntArrayElements(arr,parr,JNI_COMMIT);
}

JNIEXPORT jintArray JNICALL Java_com_bryan_jni_BasicJNI_getIntArray(JNIEnv *env, jobject jobj, jint len){
    jintArray iarr=env->NewIntArray(len);
    jint *elements=env->GetIntArrayElements(iarr,JNI_FALSE);
    int i=0;
    for(;i<len;i++){
        elements[i]=i;
    }
    env->ReleaseIntArrayElements(iarr,elements,JNI_COMMIT);
    return iarr;

}

/**

// 局部引用
// 作用：C使用到或自行创建Java对象，需要告知虚拟机在合适的时候回收对象

//局部引用，通过DeleteLocalRef手动释放对象
//1.访问一个很大的java对象，使用完之后，还要进行复杂的耗时操作
//2.创建了大量的局部引用，占用了太多的内存，而且这些局部引用跟后面的操作没有关联性

*/

JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_localRef(JNIEnv *env, jobject jobj){
    jclass dateClazz=env->FindClass("java/util/Date");
    jmethodID mid=env->GetMethodID(dateClazz,"<init>","()V");
    jobject dateObj=env->NewObject(dateClazz,mid);
    //创建一个局部引用
    jobject dateLocalRef=env->NewLocalRef(dateObj);

    //
    //省略N行代码
    //
    printf("NewLocalRef\n");
    //不再使用对象,则通知GC回收对象
    env->DeleteLocalRef(dateLocalRef);
     // 因为dateObject也是局部对象，可以直接回收dateObject对象
    //env->DeleteLocalRef(dateObj);

}


/**

// 全局引用
// 定义全局引用
//共享(可以跨多个线程)，手动控制内存使用

*/

jstring globalStr;
jint tint;

JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_createGlobalRef(JNIEnv *env, jobject jobj){
    jstring jstr=env->NewStringUTF("I love you!");
    //创建一个全局引用
    globalStr=(jstring)env->NewGlobalRef(jstr);
    //基本类型不需要使用GlobalRef
    tint=100;
    printf("NewGlobalRef\n");

}


JNIEXPORT jstring JNICALL Java_com_bryan_jni_BasicJNI_useGlobalRef(JNIEnv *env, jobject jobj){
    return globalStr;

}


JNIEXPORT void JNICALL Java_com_bryan_jni_BasicJNI_deleteGlobalRef(JNIEnv *env, jobject jobj){
    //释放全局引用
    env->DeleteGlobalRef(globalStr);
    printf("DeleteGlobalRef\n");
}

//弱全局引用
//节省内存，在内存不足时可以是释放所引用的对象
//可以引用一个不常用的对象，如果为NULL，临时创建
//创建：NewWeakGlobalRef,销毁：DeleteGlobalWeakRef
