#include "Localization.h"
#include "Native.h"

SCAN_NATIVE(Localization, GetText, "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 48 89 7C 24 ?? 41 56 48 83 EC 20 4C 8B 35")
SCAN_NATIVE(Localization, IsValid, "40 53 48 83 EC 20 44 8B 41 ?? 48 8B D9 48 8B 49 ?? 44 8B CA BA 04 00 00 00 E8 ?? ?? ?? ?? 48 8B C8")