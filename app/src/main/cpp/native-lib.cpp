#include <jni.h>
#include <string>
#include "java_call_native.h"
#include "androidlog.h"
#include "base64.h"
#include "sha256.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_sumTwoNumber(JNIEnv *env, jobject thiz, jint a, jint b) {
    auto *pNative = new JavaCallNative();
    int sum = JavaCallNative::sunTwoNumber(a, b);
    delete pNative;
    return sum;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_bubbleSort(JNIEnv *env, jobject thiz, jintArray array,
                                                jint len) {
    jint *pInt = env->GetIntArrayElements(array, nullptr);
    auto *pNative = new JavaCallNative();
    pNative->bubbleSort(pInt, len);
    delete pNative;
    //必须使用,否则array被占用,获取到的仍然是元数据
    env->ReleaseIntArrayElements(array, pInt, 0);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_newJavaBookBean(JNIEnv *env, jobject thiz, jstring bookName,
                                                     jstring author, jdouble price) {
    //转char便于打印接收到的值
    const char *bookNamePoint = env->GetStringUTFChars(bookName, NULL);
    const char *authorPoint = env->GetStringUTFChars(author, NULL);
    LOGD("########## bookName %s", bookNamePoint);
    LOGD("########## author %s", authorPoint);
    LOGD("########## price %f", price);
    jclass javaBookBeanClass = env->FindClass("com/aihuishou/jni_demo/JavaBookBean");
    if (javaBookBeanClass == NULL) {
        LOGD("########## not found JavaBookBean class ");
        return nullptr;
    }
    const char *constructorMethodName = "<init>";
    jmethodID constructorMethodID = env->GetMethodID(javaBookBeanClass, constructorMethodName,
                                                     "(Ljava/lang/String;Ljava/lang/String;D)V");
    if (constructorMethodID == NULL) {
        LOGD("########## not found JavaBookBean class constructor Method ");
        return nullptr;
    }
    jobject javaBookBeanInstance = env->NewObject(javaBookBeanClass, constructorMethodID, bookName,
                                                  author,
                                                  price);
    env->ReleaseStringUTFChars(bookName, bookNamePoint);
    env->ReleaseStringUTFChars(author, authorPoint);
    return javaBookBeanInstance;

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_encode(JNIEnv *env, jobject thiz, jstring msg) {
    // 解密字符串的 长度
    auto length = (size_t) env->GetStringUTFLength(msg);

    // 解密字符串的 内容
    const char *c_msg = env->GetStringUTFChars(msg, nullptr);

    LOGD("########## c_msg %s", c_msg);

    const std::string &encode = base64_encode(reinterpret_cast<const unsigned char *>(c_msg),
                                              length);

    LOGD("########## encode %s", encode.c_str());

    env->ReleaseStringUTFChars(msg, c_msg);

    // 解密后的字符串
    return env->NewStringUTF(encode.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_decode(JNIEnv *env, jobject thiz, jstring msg) {

    const char *c_msg = env->GetStringUTFChars(msg, nullptr);

    LOGD("########## c_msg %s", c_msg);

    const std::string &decode = base64_decode(c_msg);

    LOGD("########## decode %s", decode.c_str());

    env->ReleaseStringUTFChars(msg, c_msg);

    return env->NewStringUTF(decode.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_sha256(JNIEnv *env, jobject thiz, jstring msg) {

    const char *c_msg = env->GetStringUTFChars(msg, nullptr);

    LOGD("########## c_msg %s", c_msg);

    const std::string &result = sha256(c_msg);

    LOGD("########## sha256 %s", result.c_str());

    env->ReleaseStringUTFChars(msg, c_msg);

    return env->NewStringUTF(result.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_encrypt(JNIEnv *env, jobject thiz, jstring string,
                                             jstring key) {

}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_aihuishou_jni_1demo_JniUtil_decrypt(JNIEnv *env, jobject thiz, jstring string,
                                             jstring key) {

}