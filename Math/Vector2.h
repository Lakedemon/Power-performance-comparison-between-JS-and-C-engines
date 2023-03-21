#ifndef OPENGLENGINE_VECTOR2_H
#define OPENGLENGINE_VECTOR2_H

#include "glMath.h"
#include <cmath>

struct Vector2 {
    float x, y;
    Vector2(float x, float y);

    [[nodiscard]] float magnitude() const;
    [[nodiscard]] Vector2 normalized() const;

    static Vector2 one;
    static Vector2 zero;
    static Vector2 up;
    static Vector2 down;
    static Vector2 left;
    static Vector2 right;

    static int side(Vector2 depended, Vector2 control, Vector2 normal);
    static float angle(Vector2 a, Vector2 b);
    static float dot(Vector2 a, Vector2 b);
    static float distance(Vector2 a, Vector2 b);
    static float cross(Vector2 a, Vector2 b);

    Vector2 operator+(const Vector2 &b) const;
    Vector2 operator-(const Vector2 &b) const;
    Vector2 operator*(const Vector2 &b) const;
    Vector2 operator*(const float &b) const;
    Vector2 operator/(const float &b) const;
};

#endif //OPENGLENGINE_VECTOR2_H
