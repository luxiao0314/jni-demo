package com.aihuishou.jni_demo

import android.os.Parcel
import android.os.Parcelable
import java.io.Serializable

class JavaBookBean(
    var name: String = "",
    var author: String = "",
    var price: Double = 0.0
) : Serializable {
    override fun toString(): String {
        return "JavaBookBean(name='$name', author='$author', price=$price)"
    }
}