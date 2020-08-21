package com.aihuishou.jni_demo

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.aihuishou.aes.util.AesActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = JniUtil.stringFromJNI()

        sample_text.setOnClickListener {
            startActivity(Intent(this, AesActivity::class.java))
        }
    }
}
