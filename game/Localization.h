#pragma once

#include "Native.h"

DECLARE_NATIVE_FUNC(Localization, GetText, const char*, (int, const char*, bool*))
DECLARE_NATIVE_FUNC(Localization, IsValid, bool, (void*, int))

DECLARE_NATIVE(Localization,
    MEMBER(GetText)
    MEMBER(IsValid)
)