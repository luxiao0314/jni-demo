#ifndef JAVA_CALL_NATIVE_H
#define JAVA_CALL_NATIVE_H

#include <jni.h>

class JavaCallNative {

public:
    static int sunTwoNumber(int a, int b);

    static void bubbleSort(int *array, int arrayLength);

    static jstring md5();
};

#endif