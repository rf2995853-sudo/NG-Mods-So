#include <jni.h>
#include <android/log.h>

#define TAG "NG_MODS"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

bool NGModsAutoRun;
bool (*orig_NGMods_Running)(void *instance);

bool hook_NGMods_Running(void *instance) {
    if (NGModsAutoRun) {
        return true;
    }
    return orig_NGMods_Running(instance);
}

__attribute__((constructor)) void entry() {
    LOGD("NG Mods Library Loaded!");
    
    void *target_method = (void *)Il2CppGetMethodOffset(
        OBFUSCATE("Assembly-CSharp.dll"), 
        OBFUSCATE("COW.GamePlay"), 
        OBFUSCATE("Player"), 
        OBFUSCATE("get_IsFastRunning"), 
        0
    );

    if (target_method) {
        DobbyHook(target_method, (void *)hook_NGMods_Running, (void **)&orig_NGMods_Running);
        LOGD("NGMods DobbyHook Applied Successfully!");
    } else {
        LOGD("NGMods DobbyHook Failed: Method not found!");
    }
}
