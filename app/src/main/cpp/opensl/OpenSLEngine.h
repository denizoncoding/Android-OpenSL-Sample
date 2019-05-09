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

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <android/log.h>
#include <pthread.h>

class OpenSLEngine {

public:
    bool createEngine(int sampleRate, int bufferSize);

    bool destroyEngine();

private:

    SLObjectItf sl_engine_object_itf = nullptr;
    SLEngineItf sl_engine_engine_itf = nullptr;
    SLObjectItf sl_output_mix_object_itf = nullptr;
};


