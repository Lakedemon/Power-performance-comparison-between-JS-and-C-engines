#ifndef OPENGLENGINE_GLMATH_H
#define OPENGLENGINE_GLMATH_H

#include <cmath>

struct glMath {
public:
    constexpr static const float M_PI_180 = M_PI / 180;
    constexpr static const float M_180_PI = 180 / M_PI;
    constexpr static const float EPSILON = 0.000001f;
    constexpr static const int LUMENS_PER_WATT = 683;

    static float toDeg(float r);
    static float toRad(float d);
    static float clampUnit(float n);
    static float toHFOV(float fov, float aspect);
    static float toYFOV(float fov, float aspect);
    static float toPower(float intensity);
};

#endif //OPENGLENGINE_GLMATH_H