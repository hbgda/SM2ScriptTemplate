#pragma once

#include "Native.h"

#include <cstdint>

class AssetHash {
public:
    uint32_t hash[2] = {0, 0};

    // AssetHash(const char* asset_path);
    static AssetHash FromAssetPath(const char* asset_path);
    inline uint64_t ToInt() {
        return hash[0] | (uint64_t)hash[1] << 32;
    }
};

DECLARE_NATIVE_FUNC(AssetHash, FromAssetPath, ::AssetHash, (::AssetHash*, const char*))

DECLARE_NATIVE(AssetHash, 
    MEMBER(FromAssetPath)
)