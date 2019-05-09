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

public class OpenSLEngineController {

    static {

        System.loadLibrary("native-lib");
    }

    public native String stringFromJNI();

    public native boolean createEngine(int sampleRate, int bufferSize);

    private boolean isEngineReady = false;

    public OpenSLEngineController(int sampleRate, int bufferSize) {

        isEngineReady = createEngine(sampleRate, bufferSize);
    }

    public String getDemoString() {

        return stringFromJNI() + ": " + isEngineReady;
    }
}
