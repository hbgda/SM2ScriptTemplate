#pragma once

#include "Native.h"
#include "ActorHandle.h"
#include "Transform.h"
#include "AssetHash.h"
#include "../logging.h"

class ModelInst;
class SyncManager;
class Component;
class ComponentInfo;
class ComponentEntry;

class Actor {
    enum Flags : uint32_t {
        Enabled,
        Spawned,
        _3,
        _4,
        _5,
        _6,
        _7,
        _8,
        _9,
        _10,
        _11,
        _12,
        _13,
        UpdateEnabled
    };
    Transform* transform;
    uint32_t flags;
    uint16_t handle_lower;
    uint32_t handle_upper;
    char _0x12[0x54];
    ComponentEntry* component_list;
    short component_count;
    char _0x72[0x38];
    char* name;
public:
    inline ActorHandle GetHandle() {
        return ActorHandle(handle_upper, handle_lower);
    }

    inline void SetPosition(Vector3 &pos) {
        if (transform)
            transform->SetPosition(pos);
    }

    inline Vector3& GetPosition() {
        if (transform)
            return transform->GetPosition();
        static Vector3 invalid = Vector3 { -1e6, -1e6, -1e6 }; 
        return invalid;
    }

    inline Transform* GetTransform() {
        return transform;
    }

    inline ModelInst* GetModelInst() { 
        return (ModelInst*)transform;
    }

    void Enable();
    void Destroy();
    void EnableUpdate();

    // inline void LogComponents() {
    //     for (int i = 0; i < component_count; i++) {
    //         DEBUG("Component[%d] = %s", i, component_list[i].info->name);
    //     }
    // }

    inline uint32_t GetComponentCount() {
        return component_count;
    }

    inline ComponentEntry* GetComponentEntries() {
        return component_list;
    }

    Component* GetComponent(const char* name);

    template<typename T>
    inline T* GetComponent(const char* name) {
        return (T*)GetComponent(name);
    }


    template<typename T>
    inline T* GetComponent() {
        return GetComponent<T>(T::ComponentName);
    }

    // Components use <Component>Prius intstances for init data,
    // you will need to create a valid instance of the correct prius yourself
    Component* AddComponent(ComponentInfo* info, void* component_prius);
    Component* AddComponent(const char* name, void* component_prius);

    template<typename T>
    T* AddComponent(ComponentInfo* info, void* component_prius) {
        return (T*)AddComponent(info, component_prius);
    }

    template<typename T>
    T* AddComponent(const char* name, void* component_prius) {
        return (T*)AddComponent(name, component_prius);
    }

    template<typename T>
    T* AddComponent(void* component_prius) {
        return (T*)AddComponent(T::ComponentName, component_prius);
    }
};

DECLARE_NATIVE_FUNC(Actor, SpawnActor, ::Actor*, (::AssetHash, SpatialData&))
DECLARE_NATIVE_FUNC(Actor, SpawnActor2, ::Actor*, (::AssetHash, SyncManager*, SpatialData&))
DECLARE_NATIVE_FUNC(Actor, GetActor, ::Actor*, (ActorHandle*))

DECLARE_NATIVE_FUNC(Actor, Enable, void, (::Actor*))
DECLARE_NATIVE_FUNC(Actor, Destroy, void, (::Actor*))
DECLARE_NATIVE_FUNC(Actor, EnableUpdate, void, (::Actor*))
DECLARE_NATIVE_FUNC(Actor, AddComponent, ::Component*, (::Actor*, ComponentInfo*, void*))
DECLARE_NATIVE_FUNC(Actor, GetComponent1, ::Component*, (void*, ComponentInfo*))
DECLARE_NATIVE_FUNC(Actor, GetComponent2, ::Component*, (void*, ComponentInfo*))


DECLARE_NATIVE(Actor,
    MEMBER(GetActor)
    MEMBER(SpawnActor)
    MEMBER(SpawnActor2)

    MEMBER(Enable)
    MEMBER(Destroy)
    // MEMBER(EnableUpdate)
    MEMBER(AddComponent)
    MEMBER(GetComponent1)
    MEMBER(GetComponent2)
)

Actor* SpawnActor(AssetHash hash, SpatialData &spatial_data);
Actor* SpawnActor2(AssetHash hash, SyncManager* sync_manager, SpatialData &spatial_data);
Actor* GetActor(ActorHandle* handle);

DECLARE_NATIVE_FUNC(ActorUtils, SpawnGenericVolumeActor, ::Actor*, (bool))
DECLARE_NATIVE_FUNC(ActorUtils, SetActorModel, bool, (::Actor*, ::AssetHash))

namespace ActorUtils {
    Actor* SpawnGenericVolumeActor(bool activate);
    bool SetActorModel(Actor* actor, AssetHash model_hash);
}