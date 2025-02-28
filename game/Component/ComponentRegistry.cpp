#include "ComponentRegistry.h"
#include "Component.h"

SCAN_NATIVE_REF(ComponentRegistry, Instance, "48 8D 0D ** ** ** ** E8 ?? ?? ?? ?? 49 8B 4E ?? 48 8D 54 24 ?? 48 83 C1 58")
SCAN_NATIVE_CALL(ComponentRegistry, GetComponentInfo, "E8 ** ** ** ** 49 8B 4E ?? 48 8D 54 24 ?? 48 83 C1 58")

ComponentRegistry* GetComponentRegistry() {
    return Native::ComponentRegistry::Instance;
}

ComponentInfo* ComponentRegistry::GetComponentInfo(uint32_t name_hash) {
    return Native::ComponentRegistry::GetComponentInfo(this, name_hash);
}