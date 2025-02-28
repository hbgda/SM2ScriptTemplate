#pragma once

#include <cstdint>

class ActorHandle {
private:
    uint32_t handle;
public:
    ActorHandle(): handle(0) {};
    ActorHandle(uint32_t upper, uint32_t lower) {
        handle = (upper << 0x14) | lower;
    }

    bool operator==(ActorHandle &other) { return handle == other.handle; }
};