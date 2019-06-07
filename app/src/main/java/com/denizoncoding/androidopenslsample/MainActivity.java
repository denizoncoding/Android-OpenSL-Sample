/*
 * Copyright 2019 Deniz A. ATLIHAN
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// Created by deniz on 6.05.2019.
//

package com.denizoncoding.androidopenslsample;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.media.AudioManager;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private ToggleButton onOffButton;

    private OpenSLEngineController controller;

    private boolean isOn = false;


    @SuppressLint("ObsoleteSdkInt")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        if (android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.JELLY_BEAN_MR1) {

            Toast.makeText(this, "This app is not supported for your device.", Toast.LENGTH_LONG).show();

            finish();

            return;
        }

        createController();

        ((TextView) findViewById(R.id.sample_text)).setText(controller.getDemoString());

        onOffButton = findViewById(R.id.toggleButton);

        onOffButton.setOnClickListener(this);
    }

    @Override
    protected void onResume() {
        super.onResume();

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

    }

    @Override
    protected void onPause() {

        if (isOn) {

            onOffButton.performClick();
        }

        super.onPause();
    }

    @Override
    protected void onDestroy() {

        if (controller != null) {

            controller.destroy();
        }

        super.onDestroy();
    }

    @Override
    public void onClick(View v) {

        isOn = onOffButton.isChecked();

        controller.setOn(isOn);
    }

    private void createController() {

        AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);

        controller = new OpenSLEngineController(audioManager, this);
    }

}
