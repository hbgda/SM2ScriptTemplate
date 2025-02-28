#pragma once

#include "ComponentHandle.h"

#include <cstdint>

// Can prob add more to this later
#define DECLARE_COMPONENT(n) static constexpr const char* ComponentName = #n

class Actor;
class EventInfo;

typedef void (*EventHandler)(void* event);

class Component {
    void** vftable;
    void* _0x8;
    Actor* actor;
    float _0x18;
    ComponentHandle handle;
    char pad[0x28];
public:
    inline void** GetVFTable() {
        return vftable;
    }

    inline Actor* GetActor() const {
        return actor;
    }

    inline ComponentHandle GetHandle() const {
        return handle;
    }
};

class ComponentInfo {
public:
    char _0x0[0x60];
    const char* name;
};

class ComponentEntry {
public:
    ComponentInfo* info;
    Component* component;
};