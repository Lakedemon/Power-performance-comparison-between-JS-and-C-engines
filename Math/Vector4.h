#ifndef OPENGLENGINE_Vector4_H
#define OPENGLENGINE_Vector4_H

#include "glMath.h"
#include <cmath>

struct Vector4 {
    float x, y, z, w;
    Vector4(float x, float y, float z, float w);
    explicit Vector4(const float* xyzw);

    [[nodiscard]] float magnitude() const;
    [[nodiscard]] Vector4 normalized() const;

    static Vector4 one;
    static Vector4 zero;

    static int side(Vector4 depended, Vector4 control, Vector4 normal);
    static float angle(Vector4 a, Vector4 b);
    static float dot(Vector4 a, Vector4 b);
    static float distance(Vector4 a, Vector4 b);

    Vector4 operator+(const Vector4 &b) const;
    Vector4 operator-(const Vector4 &b) const;
    Vector4 operator-() const;
    Vector4 operator*(const Vector4 &b) const;
    Vector4 operator*(const float &b) const;
    Vector4 operator/(const float &b) const;
};

#endif //OPENGLENGINE_Vector4_H
