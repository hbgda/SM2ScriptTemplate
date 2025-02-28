#include "ModSettings.h"

#include "menu.h"

#include "game/Native.h"
#include "game/HeroSystem.h"
#include "game/Component/Health.h"

#include "utils.h"
#include "logging.h"
#include "hooking.h"

#include <Windows.h>



BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // utils::create_console();
        MH_Initialize();
        Native::Init(); 
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void script_enable() {
    ModSettings::RegisterMenu<HealthMenu>();
}
