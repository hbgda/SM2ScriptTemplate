#pragma once

#include "Native.h"

typedef struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
} Vector3;

inline Vector3 operator*(float scalar, const Vector3& v) {
    return v * scalar;
}

typedef struct {
    char _0x0[0x30];
    Vector3 pos;
} SpatialData;

class Transform {
public:
    SpatialData spatial_data;

    inline Vector3& GetPosition() {
        return spatial_data.pos;
    }

    float GetRotation();

    void SetRotation(float radians);
    void SetPosition(Vector3 &pos);
};

DECLARE_NATIVE_FUNC(Transform, SetPosition, void, (::Transform*, Vector3*))

DECLARE_NATIVE(Transform,
    MEMBER(SetPosition)
)