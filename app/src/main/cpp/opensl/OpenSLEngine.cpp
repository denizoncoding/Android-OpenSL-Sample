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
#define MILLIHERTZ_IN_HERTZ 1000


SLAndroidSimpleBufferQueueItf pcmBufferQueue;
uint8_t *out_buffer;
bool temporaryOnOff = false;

void
bufferCallBack(SLAndroidSimpleBufferQueueItf bf, void *context) {


    for (int i = 0; i < (1762); i++) {

        if (temporaryOnOff) {
            int j = (i / 80) % 2;

            if (j == 0) {
                out_buffer[i] = static_cast<uint8_t>(232);
            } else {
                out_buffer[i] = static_cast<uint8_t>(0);
            }
        } else {

            out_buffer[i] = static_cast<uint8_t>(0);
        }
    }

    SLresult result;

    result = (*pcmBufferQueue)->Enqueue(pcmBufferQueue, out_buffer, 441);

    if (SL_RESULT_SUCCESS != result) {

        __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Sound error");
    }
}

bool OpenSLEngine::createEngine() {

    SLresult result;

    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine creation is started.");

    result = slCreateEngine(&slEngineObject, 0, NULL, 0, NULL, NULL);

    if (result != SL_RESULT_SUCCESS) {

        __android_log_print(ANDROID_LOG_ERROR, DEBUG_TAG, "Engine creation is failed.");
        return false;
    }

    result = (*slEngineObject)->Realize(slEngineObject, SL_BOOLEAN_FALSE);


    if (result != SL_RESULT_SUCCESS) {

        __android_log_print(ANDROID_LOG_ERROR, DEBUG_TAG, "Engine realization is failed.");
        return false;
    }

    result = (*slEngineObject)->GetInterface(slEngineObject, SL_IID_ENGINE, &slEngineInterface);


    if (result != SL_RESULT_SUCCESS) {

        __android_log_print(ANDROID_LOG_ERROR, DEBUG_TAG, "Engine Interface getting is failed.");
        return false;
    }

    __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine creation finished SUCCESSFULLY.");

    return true;
}

bool OpenSLEngine::createAudioPlayer(int sampleRate, int bufferSize) {

    SLresult result;

    this->sampleRate = sampleRate;
    this->bufferSize = bufferSize;

    result = result & generateOutputBuffer();

    result = result & setEnviromentalReverb();

    result = result & setBufferQueue();

    result = result & setPcmInterfaces();

    bufferCallBack(pcmBufferQueue, NULL);

    if (result == SL_RESULT_SUCCESS) {

        __android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, "Engine ready");

        return true;

    } else {

        return false;
    }
}

SLresult OpenSLEngine::setPcmInterfaces() {

    (*slPcmObjInterface)->Realize(slPcmObjInterface, SL_BOOLEAN_FALSE);
    (*slPcmObjInterface)->GetInterface(slPcmObjInterface, SL_IID_PLAY, &slPcmPlayerInterface);
    (*slPcmObjInterface)->GetInterface(slPcmObjInterface, SL_IID_BUFFERQUEUE, &pcmBufferQueue);
    (*pcmBufferQueue)->RegisterCallback(pcmBufferQueue, bufferCallBack, NULL);
    (*slPcmObjInterface)->GetInterface(slPcmObjInterface, SL_IID_VOLUME, &slPcmVolumeInterface);
    (*slPcmPlayerInterface)->SetPlayState(slPcmPlayerInterface, SL_PLAYSTATE_PLAYING);

    return SL_RESULT_SUCCESS;
}

SLresult OpenSLEngine::setBufferQueue() {

    SLresult result;

    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, slOutputMixObjInterface};

    SLDataSink audioSink = {&outputMix, NULL};

    SLDataLocator_AndroidSimpleBufferQueue androidBufferQueue = {
            SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE,
            2};

    //TODO: sampleRate from external
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            2,
            SL_SAMPLINGRATE_44_1,
//            ((SLuint32) sampleRate) * MILLIHERTZ_IN_HERTZ,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN
    };

    SLDataSource slDataSource = {&androidBufferQueue, &pcm};

    SLInterfaceID interfaceIds[2] = {SL_IID_ANDROIDSIMPLEBUFFERQUEUE,
                                     SL_IID_ANDROIDCONFIGURATION};

    SLboolean interfacesRequired[2] = {SL_BOOLEAN_TRUE,
                                       SL_BOOLEAN_TRUE};

    result = (*slEngineInterface)->CreateAudioPlayer(
            slEngineInterface,
            &slPcmObjInterface,
            &slDataSource,
            &audioSink,
            2,
            interfaceIds,
            interfacesRequired
    );

    return result;
}

SLresult OpenSLEngine::setEnviromentalReverb() {

    SLresult result;

    SLInterfaceID mids[1] = {SL_IID_ENVIRONMENTALREVERB};

    SLboolean mreq[1] = {SL_BOOLEAN_FALSE};

    result = (*slEngineInterface)->CreateOutputMix(slEngineInterface, &slOutputMixObjInterface, 1,
                                                   mids, mreq);

    if (result != SL_RESULT_SUCCESS) {

        return result;
    }

    result = (*slOutputMixObjInterface)->Realize(slOutputMixObjInterface, SL_BOOLEAN_FALSE);

    if (result != SL_RESULT_SUCCESS) {

        return result;
    }

    result = (*slOutputMixObjInterface)->GetInterface(slOutputMixObjInterface,
                                                      SL_IID_ENVIRONMENTALREVERB,
                                                      &slReverbInterface);

    return result;
}

SLresult OpenSLEngine::generateOutputBuffer() {

    //TODO: buffersize from external
    out_buffer = (uint8_t *) malloc(static_cast<size_t>(44100 * 2 * 0.2f));

    return SL_RESULT_SUCCESS;
}

bool OpenSLEngine::destroyEngine() {

    if (slEngineObject != nullptr) {

        (*slEngineObject)->Destroy(slEngineObject);
    }

    if (slOutputMixObjInterface != nullptr) {

        (*slOutputMixObjInterface)->Destroy(slOutputMixObjInterface);
    }

    if (slPcmObjInterface != nullptr) {

        (*slPcmObjInterface)->Destroy(slPcmObjInterface);
    }

}

void OpenSLEngine::setOnOff(bool onOff) {

    temporaryOnOff = onOff;
}