#include "AssetHash.h"

SCAN_NATIVE(AssetHash, FromAssetPath, "40 53 48 83 EC 20 48 8B C2 48 8B D9 48 85 D2 74 ?? 80 3A 00 74 ?? 48 BA 42 0F 87 D7 95 57 6C C9")

AssetHash AssetHash::FromAssetPath(const char* asset_path) {
    AssetHash hash;
    Native::AssetHash::FromAssetPath(&hash, asset_path);
    return hash;
}