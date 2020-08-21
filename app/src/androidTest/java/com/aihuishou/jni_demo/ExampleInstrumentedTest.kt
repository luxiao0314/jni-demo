package com.aihuishou.jni_demo

import android.util.Log
import androidx.test.platform.app.InstrumentationRegistry
import androidx.test.ext.junit.runners.AndroidJUnit4

import org.junit.Test
import org.junit.runner.RunWith

import org.junit.Assert.*
import java.util.*

/**
 * Instrumented test, which will execute on an Android device.
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
@RunWith(AndroidJUnit4::class)
class ExampleInstrumentedTest {

    val TAG = this.javaClass.simpleName

    @Test
    fun useAppContext() {
        // Context of the app under test.
        val appContext = InstrumentationRegistry.getInstrumentation().targetContext
        assertEquals("com.aihuishou.jni_demo", appContext.packageName)
    }

    @Test
    fun sumTwoNumber() {
        val sum = JniUtil.sumTwoNumber(1, 6)
        Log.d(TAG, sum.toString())
    }

    @Test
    fun bubbleSort() {
        val arrays = intArrayOf(12, 23, 13, 16, 1, 4, 2, 10)
        JniUtil.bubbleSort(arrays, arrays.size)
        Log.d(TAG, arrays.contentToString())
    }

    @Test
    fun newJavaBookBean() {
        val book = JniUtil.newJavaBookBean("aaa", "lux", 100.0)
        Log.d(TAG, book.toString())
    }

    @Test
    fun encode() {
        val str = "123456"
        val encode = JniUtil.encode(str)
        Log.d(TAG, encode)
    }

    @Test
    fun decode() {
        val str = "MTIzNDU2"
        val decode = JniUtil.decode(str)
        Log.d(TAG, decode)
    }

    @Test
    fun sha256() {
        val str = "123456"
        val decode = JniUtil.sha256(str)
        //8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92
        Log.d(TAG, decode)
    }
}