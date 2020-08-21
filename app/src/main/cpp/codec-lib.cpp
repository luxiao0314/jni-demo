#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include "blowfish.h"
#include "base64.h"
#include "sha256.h"
#include "common.h"

using namespace std;

#define LOG_TAG "Codec"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__)


extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_mta_sdk_utils_EncryptUtils_encrypt(JNIEnv * env, jclass jc, jbyteArray jbaSrc, jbyteArray jbaKey) {

    //convert jbyteArray to vector<char>
    unsigned char * isCopy;
    jbyte* jbae = env->GetByteArrayElements(jbaKey, isCopy);
    jsize len = env->GetArrayLength(jbaKey);
    char * key = (char *)jbae;
    vector<char> keyV;
    for (int i = 0; i < len; i++) {
        keyV.push_back(key[i]);
    }

    jbae = env->GetByteArrayElements(jbaSrc, isCopy);
    len = env->GetArrayLength(jbaSrc);
    char * src = (char *)jbae;
    vector<char> srcV;
    for (int i = 0; i < len; i++) {
        srcV.push_back(src[i]);
    }

    Blowfish blowfish(keyV);
    vector<char> desV = blowfish.Encrypt(srcV);

    //convert vector<char> to jbyteArray
    jbyte* result_e = new jbyte[desV.size()];
    jbyteArray result = env->NewByteArray(desV.size());
    for (int i = 0; i < desV.size(); i++) {
        result_e[i] = (jbyte)desV[i];
    }

    env->ReleaseByteArrayElements(jbaSrc, jbae, 0); // 释放内存

    env->SetByteArrayRegion(result, 0, desV.size(), result_e);
    return result;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_mta_sdk_utils_EncryptUtils_decrypt(JNIEnv * env, jclass jc, jbyteArray jbaSrc, jbyteArray jbaKey) {

    //convert jbyteArray to vector<char>
    unsigned char * isCopy;
    jbyte* jbae = env->GetByteArrayElements(jbaKey, isCopy);
    jsize len = env->GetArrayLength(jbaKey);
    char * key = (char *)jbae;
    vector<char> keyV;
    for (int i = 0; i < len; i++) {
        keyV.push_back(key[i]);
    }

    jbae = env->GetByteArrayElements(jbaSrc, isCopy);
    len = env->GetArrayLength(jbaSrc);
    char * src = (char *)jbae;
    vector<char> srcV;
    for (int i = 0; i < len; i++) {
        srcV.push_back(src[i]);
    }

    Blowfish blowfish(keyV);
    vector<char> desV = blowfish.Decrypt(srcV);

    //convert vector<char> to jbyteArray
    jbyte* result_e = new jbyte[desV.size()];
    jbyteArray result = env->NewByteArray(desV.size());
    for (int i = 0; i < desV.size(); i++) {
        result_e[i] = (jbyte)desV[i];
    }

    env->ReleaseByteArrayElements(jbaSrc, jbae, 0); // 释放内存

    env->SetByteArrayRegion(result, 0, desV.size(), result_e);
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mta_sdk_utils_EncryptUtils_getFileKey(JNIEnv * env, jclass jc,jstring jwtToken) {

    const char *jwt_token_str = env->GetStringUTFChars(jwtToken, 0);
    string jwt = jwt_token_str;

    string file_key = getFileKey(jwt);

    return env->NewStringUTF(file_key.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_mta_sdk_utils_EncryptUtils_sign(JNIEnv * env, jclass jc, jobject hashMap,jstring jwtToken) {


    const char *jwt_token_str = env->GetStringUTFChars(jwtToken, 0);
    string jwt = jwt_token_str;

    // 开始解析 hashMap

    jclass c_map = env->GetObjectClass(hashMap);
    jmethodID id_entrySet = env->GetMethodID(c_map, "entrySet", "()Ljava/util/Set;");

    jclass c_entryset = env->FindClass("java/util/Set");
    jmethodID id_iterator = env->GetMethodID(c_entryset, "iterator", "()Ljava/util/Iterator;");

    jclass c_iterator = env->FindClass("java/util/Iterator");
    jmethodID id_hasNext = env->GetMethodID(c_iterator, "hasNext", "()Z");
    jmethodID id_next = env->GetMethodID(c_iterator, "next", "()Ljava/lang/Object;");

    jclass c_entry = env->FindClass("java/util/Map$Entry");
    jmethodID id_getKey = env->GetMethodID(c_entry, "getKey", "()Ljava/lang/Object;");
    jmethodID id_getValue = env->GetMethodID(c_entry, "getValue", "()Ljava/lang/Object;");

    jclass c_string = env->FindClass("java/lang/String");
    jmethodID id_toString = env->GetMethodID(c_string, "toString", "()Ljava/lang/String;");

    jobject obj_entrySet = env->CallObjectMethod(hashMap, id_entrySet);
    jobject obj_iterator = env->CallObjectMethod(obj_entrySet, id_iterator);

    map<string, string> resultmap;

    bool hasNext = (bool) env->CallBooleanMethod(obj_iterator, id_hasNext);

    while(hasNext) {
        jobject entry = env->CallObjectMethod(obj_iterator, id_next);

        jobject key = env->CallObjectMethod(entry, id_getKey);
        jobject value = env->CallObjectMethod(entry, id_getValue);

        jstring jstrKey = (jstring) env->CallObjectMethod(key, id_toString);
        jstring jstrValue = (jstring) env->CallObjectMethod(value, id_toString);

        const char *strKey = env->GetStringUTFChars(jstrKey, 0);
        const char *strValue = env->GetStringUTFChars(jstrValue, 0);

        resultmap.insert(pair<string,string> ( strKey, strValue ));

        hasNext = (bool) env->CallBooleanMethod(obj_iterator, id_hasNext);
    }

    string output = sign(resultmap,jwt);

    return env->NewStringUTF(output.c_str());
}