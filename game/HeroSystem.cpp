#include "HeroSystem.h"

SCAN_NATIVE_REF(HeroSystem, Instance, "48 89 05 ** ** ** ** 89 35 ?? ?? ?? ?? 48 89 35")

HeroSystem* GetHeroSystem() {
    return Native::HeroSystem::Instance;
}