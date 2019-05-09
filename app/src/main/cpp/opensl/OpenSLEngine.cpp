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

#include "OpenSLEngine.h"

#define DEBUG_TAG "OpenSLEngine:"


bool OpenSLEngine::createEngine(int sampleRate, int bufferSize) {

    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine creation is started.");

    SLresult result;

    result = slCreateEngine(&sl_engine_object_itf,
                            0, /* numOptions */
                            nullptr, /* pEngineOptions */
                            0, /* numInterfaces */
                            nullptr, /* pInterfaceIds */
                            nullptr /* pInterfaceRequired */);
    if (result != SL_RESULT_SUCCESS) {

        destroyEngine();
        return false;
    }

    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine is created.");

    result = (*sl_engine_object_itf)->Realize(sl_engine_object_itf, SL_BOOLEAN_FALSE /* async */);

    if (result != SL_RESULT_SUCCESS) {

        destroyEngine();
        return false;
    }
    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine is realized.");

    result = (*sl_engine_object_itf)->GetInterface(sl_engine_object_itf,
                                                   SL_IID_ENGINE,
                                                   &sl_engine_engine_itf);

    if (result != SL_RESULT_SUCCESS) {

        destroyEngine();
        return false;
    }
    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine interface get.");

    result = (*sl_engine_engine_itf)->CreateOutputMix(sl_engine_engine_itf,
                                                      &sl_output_mix_object_itf,
                                                      0,
                                                      nullptr,
                                                      nullptr);
    if (result != SL_RESULT_SUCCESS) {

        destroyEngine();
        return false;
    }

    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Output mix is created.");

    result = (*sl_output_mix_object_itf)->Realize(sl_output_mix_object_itf,
                                                  SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) {

        destroyEngine();
        return false;
    }

    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Output mix is realized.");


    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine is created SUCCESSFULLY.");

    return true;
}


bool OpenSLEngine::destroyEngine() {

    if (sl_output_mix_object_itf != nullptr) {
        (*sl_output_mix_object_itf)->Destroy(sl_output_mix_object_itf);
        sl_output_mix_object_itf = nullptr;
    }
    if (sl_engine_object_itf != nullptr) {
        (*sl_engine_object_itf)->Destroy(sl_engine_object_itf);
        sl_engine_object_itf = nullptr;
    }
}

bool OpenSLEngine::createAudioPlayer() {
}