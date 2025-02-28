#pragma once
#include <cstdint>

#include <Windows.h>
#include "../logging.h"

class Asset {
public:
    enum Status : uint8_t {
        Loading = 2,
        Loaded = 4
    };
    
    volatile Status status;
    char _0x4[0x9];
    const char* path;

    // Don't use this in the main thread
    inline void WaitUntilLoaded() {
        while (status != Status::Loaded) {
            Sleep(100);
        }
    }
};