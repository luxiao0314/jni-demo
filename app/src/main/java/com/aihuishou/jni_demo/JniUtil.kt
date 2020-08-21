package com.aihuishou.jni_demo

/**
 * @Description
 * @Author lux
 * @Date 2020/8/18 3:41 PM
 * @Version
 */
object JniUtil {

    init {
        System.loadLibrary("native-lib")
    }

    external fun stringFromJNI(): String

    external fun sumTwoNumber(a: Int, b: Int): Int

    external fun bubbleSort(array: IntArray, len: Int)

    external fun newJavaBookBean(bookName: String?, author: String?, price: Double): JavaBookBean

    external fun decode(string: String): String

    external fun encode(string: String): String

    external fun sha256(string: String): String

    external fun encrypt(string: String, key: String): String

    external fun decrypt(string: String, key: String): String

}
