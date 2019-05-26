#include <jni.h>
#include <string>
#include "opensl/OpenSLEngine.h"

OpenSLEngine *engine;


extern "C" JNIEXPORT jstring JNICALL
Java_com_denizoncoding_androidopenslsample_OpenSLEngineController_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "OpenSLES Hello";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_denizoncoding_androidopenslsample_OpenSLEngineController_createEngine(JNIEnv *env,
                                                                               jobject instance,
                                                                               jint sampleRate,
                                                                               jint bufferSize) {
    engine = new OpenSLEngine();

    bool isEngineCreate = engine->createEngine();

    if (!isEngineCreate) {

        return false;
    }

    return engine->createAudioPlayer(sampleRate, bufferSize);

}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_denizoncoding_androidopenslsample_OpenSLEngineController_destroyEngine(JNIEnv *env,
                                                                                jobject instance) {

    engine->destroyEngine();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_denizoncoding_androidopenslsample_OpenSLEngineController_setOnOff(JNIEnv *env,
                                                                           jobject instance,
                                                                           jboolean onOff) {

    engine->setOnOff(onOff);
}