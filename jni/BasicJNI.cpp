#include "com_bryan_jni_BasicJNI.h"
JNIEXPORT jstring JNICALL Java_com_bryan_jni_BasicJNI_helloFromC(JNIEnv *env, jclass jcls){

    return env->NewStringUTF("hello world from C");

}
