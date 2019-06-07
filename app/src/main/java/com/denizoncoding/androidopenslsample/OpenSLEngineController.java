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

import android.annotation.TargetApi;
import android.content.Context;
import android.media.AudioManager;
import android.os.Build;

public class OpenSLEngineController {

    static {

        System.loadLibrary("native-lib");
    }

    private native String stringFromJNI();

    private native boolean createEngine(int sampleRate, int bufferSize);

    private native boolean destroyEngine();

    private native void setOnOff(boolean onOff);

    private boolean isEngineReady = false;

    @TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
    public OpenSLEngineController(AudioManager audioManager, Context context) {

        /// Target Api check performed in MainActivity.

        int sampleRate = Integer.parseInt(audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE));

        int framesPerBuffer = Integer.parseInt(audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER));

        isEngineReady = createEngine(sampleRate, framesPerBuffer);
    }

    public void setOn(boolean onOff) {

        setOnOff(onOff);
    }

    public void destroy() {

        destroyEngine();
    }

    public String getDemoString() {

        return stringFromJNI() + ": " + isEngineReady;
    }
}
