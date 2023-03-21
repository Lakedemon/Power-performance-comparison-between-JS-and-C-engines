#ifndef OPENGLENGINE_VECTOR3_H
#define OPENGLENGINE_VECTOR3_H

#include "glMath.h"
#include <cmath>

struct Vector3 {
    float x, y, z;
    Vector3(float x, float y, float z);

    [[nodiscard]] float magnitude() const;
    [[nodiscard]] Vector3 normalized() const;

    static Vector3 one;
    static Vector3 zero;
    static Vector3 up;
    static Vector3 down;
    static Vector3 left;
    static Vector3 right;
    static Vector3 forward;
    static Vector3 back;

    static int side(Vector3 depended, Vector3 control, Vector3 normal);
    static float angle(Vector3 a, Vector3 b);
    static float dot(Vector3 a, Vector3 b);
    static float distance(Vector3 a, Vector3 b);
    static Vector3 cross(Vector3 a, Vector3 b);
    static Vector3 QuaternionToEuler(float qx, float qy, float qz, float qw);

    Vector3 operator+(const Vector3 &b) const;
    Vector3 operator-(const Vector3 &b) const;
    Vector3 operator*(const Vector3 &b) const;
    Vector3 operator*(const float &b) const;
    Vector3 operator/(const float &b) const;
};

#endif //OPENGLENGINE_VECTOR3_H
