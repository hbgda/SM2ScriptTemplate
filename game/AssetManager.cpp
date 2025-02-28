#include "AssetManager.h"
#include "Native.h"

SCAN_NATIVE(AssetManager, GetAssetManager, "48 0F BE C1 48 8D 0D ?? ?? ?? ?? 48 8B 04 ?? C3")
SCAN_NATIVE(AssetManager, LoadAsset, "48 89 54 24 ?? 53 56 57 41 55 41 56 48 83 EC 50 48 8B DA")

AssetManager* GetAssetManager(AssetManagerType type) {
    return Native::AssetManager::GetAssetManager(type);
}

Asset* LoadAsset(AssetManagerType type, AssetHash asset_hash) {
    return Native::AssetManager::LoadAsset(GetAssetManager(type), asset_hash, nullptr, nullptr, nullptr, nullptr, 0);
}