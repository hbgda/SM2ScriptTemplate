#include "Actor.h"
#include "Component/Component.h"
#include "Component/ComponentRegistry.h"

SCAN_NATIVE(Actor, GetActor, "44 8B 01 41 8B D0 C1 EA 14 81 E2 FF 07 00 00 74 ?? 41 81 E0 FF FF 0F 00 4B 8D 0C ?? 48 C1 E1 06 48 03 0D ?? ?? ?? ?? 44 3B 05 ?? ?? ?? ?? 73 ?? 0F B7 41 ?? 3B D0 74 ?? 33 C9 48 8B C1")
SCAN_NATIVE(Actor, SpawnActor, "40 53 48 83 EC 50 48 8B DA 48 8B D1 48 8D 0D")
SCAN_NATIVE(Actor, SpawnActor2, "48 89 5C 24 ?? 57 48 81 EC 90 00 00 00 48 8B FA 49 8B D8 48 8B D1 48 8D 0D")

SCAN_NATIVE(Actor, Enable, "48 89 5C 24 ?? 48 89 6C 24 ?? 56 57 41 56 48 81 EC 80 00 00 00 48 8B F9")
SCAN_NATIVE_CALL(Actor, Destroy, "E8 ** ** ** ** 48 8D 4B ?? C7 83 ?? ?? ?? ?? 00 00 00 00 E8")
SCAN_NATIVE(Actor, EnableUpdate, "40 56 48 83 EC 20 0F B7 51")
SCAN_NATIVE(Actor, AddComponent, "4C 8B DC 4D 89 43 ?? 49 89 53 ?? 48 83 EC 48")
SCAN_NATIVE(Actor, GetComponent1, "48 89 5C 24 ?? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 0F 84 ?? ?? ?? ?? 66 83 79 ?? 00")
SCAN_NATIVE(Actor, GetComponent2, "44 0F B7 49 ?? 4C 8B C2")

SCAN_NATIVE(ActorUtils, SpawnGenericVolumeActor, "48 89 5C 24 ?? 48 89 7C 24 ?? 55 48 8D 6C 24 ?? 48 81 EC 00 01 00 00 0F 10 0D")
SCAN_NATIVE(ActorUtils, SetActorModel, "40 57 41 56 48 81 EC B8 01 00 00")

void Actor::Enable() {
    Native::Actor::Enable(this);
}

void Actor::Destroy() {
    Native::Actor::Destroy(this);
}

void Actor::EnableUpdate() {
    Native::Actor::EnableUpdate(this);
}

// Component* Actor::GetComponent(const char* name) {
//     // DEBUG("Component Count: %d", component_count);
//     for (int i = 0; i < component_count; i++) {
//         // DEBUG("[%d] Component Name: %s", i, component_list[i].info->name);
//         if (strcmp(component_list[i].info->name, name) == 0)
//             return component_list[i].component;
//     }
//     return nullptr;
// }

Component* Actor::GetComponent(const char* name) {
    ComponentInfo* info = GetComponentRegistry()->GetComponentInfo(name);
    if (*((char*)this + 0x88) == 0) {
        return Native::Actor::GetComponent1((char*)this + 0x58, info);
    }
    else {
        return Native::Actor::GetComponent2((char*)this + 0x80, info);
    }
}

Component* Actor::AddComponent(ComponentInfo* info, void* component_prius) {
    return Native::Actor::AddComponent(this, info, component_prius);
}

Component* Actor::AddComponent(const char* name, void* component_prius) {
    ComponentInfo* component_info = GetComponentRegistry()->GetComponentInfo(name);
    if (!component_info)
        return nullptr;
    
    return AddComponent(component_info, component_prius);
}


Actor* GetActor(ActorHandle* handle) {
    return Native::Actor::GetActor(handle);
}

Actor* SpawnActor(AssetHash hash, SpatialData &spatial_data) {
    return Native::Actor::SpawnActor(hash, spatial_data);
}

Actor* SpawnActor2(AssetHash hash, SyncManager* sync_manager, SpatialData &spatial_data) {
    return Native::Actor::SpawnActor2(hash, sync_manager, spatial_data);
}

Actor* ActorUtils::SpawnGenericVolumeActor(bool activate) {
    return Native::ActorUtils::SpawnGenericVolumeActor(activate);
}

bool ActorUtils::SetActorModel(Actor* actor, AssetHash model_hash) {
    return Native::ActorUtils::SetActorModel(actor, model_hash);
}