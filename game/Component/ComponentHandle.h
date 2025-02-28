#pragma once

#include <cstdint>

class Component;

class ComponentHandle {
    uint32_t handle;
public:
    bool operator==(ComponentHandle &other) { return handle == other.handle; }
};