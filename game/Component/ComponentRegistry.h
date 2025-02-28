#pragma once

#include "../Native.h"
#include "../HashTable.h"
#include "../Hash.h"

class ComponentInfo;

class ComponentRegistry {
    HashTable<uint32_t, uint32_t> component_table;
public:
    ComponentInfo* GetComponentInfo(uint32_t name_hash);
    inline ComponentInfo* GetComponentInfo(const char* name) {
        return GetComponentInfo(StringCRC32(name));
    }
};

DECLARE_NATIVE_REF(ComponentRegistry, Instance, ::ComponentRegistry*)
DECLARE_NATIVE_FUNC(ComponentRegistry, GetComponentInfo, ComponentInfo*, (::ComponentRegistry*, uint32_t))

DECLARE_NATIVE(ComponentRegistry,
    MEMBER(Instance)
    MEMBER(GetComponentInfo)
)

ComponentRegistry* GetComponentRegistry();