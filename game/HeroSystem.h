#pragma once

#include "Native.h"
#include "Actor.h"

class HeroSystem {
    void** vftable;
    char _0x8[0x8];
    int _0x10;
    ActorHandle hero_handle;
public:
    inline Actor* GetHero() {
        return GetActor(&hero_handle);
    }
};

HeroSystem* GetHeroSystem();

DECLARE_NATIVE_REF(HeroSystem, Instance, ::HeroSystem*)

DECLARE_NATIVE(HeroSystem,
    MEMBER(Instance)
)