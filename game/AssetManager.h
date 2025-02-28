#pragma once

#include "Native.h"
#include "AssetHash.h"
#include "Asset.h"

enum AssetManagerType {
    LevelManager,
    ZoneManager,
    ActorAssetManager,
    ConduitAssetManager,
    ConfigAssetManager,
    Cinematic2Manager,
    ModelManager,
    AnimClipManager,
    AnimSetManager,
    MaterialManager,
    MaterialTemplateManager,
    TextureManager,
    AtmosphereManager,
    VisualEffectManager,
    SoundBankManager,
    LocalizationAssetManager,
    ZoneCoverManager,
    ModelVariantManager,
    LightGridManager,
    LevelLightManager,
    NodeGraphAssetManager,
    BreakableAssetManager,
    WwiseLookupAssetManager,
    TerrainAssetManager
};

class AssetManager {
    char _0x0[0x40];
public:
    char* asset_array;
    uint32_t asset_size;
    char _0x4C[0x24];
    uint32_t asset_count;

    inline Asset* GetAsset(int idx) {
        return (Asset*)(asset_array + idx * asset_size);
    }
};

AssetManager* GetAssetManager(AssetManagerType type);

Asset* LoadAsset(AssetManagerType type, AssetHash asset_hash);
inline Asset* LoadAsset(AssetManagerType type, const char* asset_path) {
    return LoadAsset(type, AssetHash::FromAssetPath(asset_path));
}

DECLARE_NATIVE_FUNC(AssetManager, GetAssetManager, ::AssetManager*, (AssetManagerType))
DECLARE_NATIVE_FUNC(AssetManager, LoadAsset, Asset*, (::AssetManager*, ::AssetHash, void*, const char*, void*, void*, int32_t))

DECLARE_NATIVE(AssetManager,
    MEMBER(GetAssetManager)
    MEMBER(LoadAsset)
)