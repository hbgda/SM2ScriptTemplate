#include "Transform.h"
#include "Native.h"

#include "../logging.h"

#include <math.h>

SCAN_NATIVE(Transform, SetPosition, "0F 10 51 ?? 4C 8B C1")

void Transform::SetPosition(Vector3 &pos) {
    Native::Transform::SetPosition(this, &pos);
}

float Transform::GetRotation() {
    return atan2f(*(float*)((uintptr_t)this + 0x28), *(float*)((uintptr_t)this + 0x20));
}

void Transform::SetRotation(float radians) {
    *(float*)((uintptr_t)this + 0x20) = cosf(radians);
    *(float*)((uintptr_t)this + 0x28) = sinf(radians);
}