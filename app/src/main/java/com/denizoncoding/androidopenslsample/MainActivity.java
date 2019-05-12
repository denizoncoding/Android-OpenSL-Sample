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

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.media.AudioManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.ToggleButton;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private ToggleButton onOffButton;

    private OpenSLEngineController controller;// = new OpenSLEngineController();

    private boolean isOn = false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        createController();

        ((TextView) findViewById(R.id.sample_text)).setText(controller.getDemoString());

        onOffButton = findViewById(R.id.toggleButton);

        onOffButton.setOnClickListener(this);
    }

    @Override
    protected void onResume() {
        super.onResume();

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

        controller.destroy();
        super.onDestroy();
    }

    @Override
    public void onClick(View v) {

        isOn = onOffButton.isChecked();

        controller.setOn(isOn);
    }

    private void createController() {

        AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);

        controller = new OpenSLEngineController(audioManager);
    }

}
