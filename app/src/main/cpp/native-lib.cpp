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

extern "C" JNIEXPORT jboolean JNICALL
Java_com_denizoncoding_androidopenslsample_OpenSLEngineController_createEngine(
        JNIEnv *env,
        jobject, jint sampleRate, jint bufferSize) {

    engine = new OpenSLEngine();

    return static_cast<jboolean>(engine->createEngine(sampleRate, bufferSize));
}
