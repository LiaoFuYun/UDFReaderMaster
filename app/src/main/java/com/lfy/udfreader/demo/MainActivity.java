package com.lfy.udfreader.demo;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import com.lfy.udfreader.UDFReader;

public class MainActivity extends AppCompatActivity {
    public static final String TAG = MainActivity.class.getSimpleName();
    private static final String mIsoPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/111.iso";     //电影文件绝对路径
    private static final String BDMV_STREAM_PATH = "/BDMV/STREAM/";
    // 10M
    private static final int ISO_SAMPLE_CLIP_LENGTH = 10 * 1024 * 1024;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void read(View view) {
        String firstClipFileName = "00001.m2ts";
        String firstClipPath = BDMV_STREAM_PATH + firstClipFileName;
        String savePath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/sample/" + firstClipFileName;
        boolean result = UDFReader.getInstance().getFirstClipSample(mIsoPath, firstClipPath, savePath, ISO_SAMPLE_CLIP_LENGTH);
        Log.d(TAG, "getClipSampleResult: " + result);
    }
}
