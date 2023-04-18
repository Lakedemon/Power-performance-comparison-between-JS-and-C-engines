#include "glMath.h"

float glMath::toDeg(float r){
    return r * M_180_PI;
}

float glMath::toRad(float d){
    return d * M_PI_180;
}

float glMath::clampUnit (float n) {
    return fmax(-1, fmin(n, 1));
}

float glMath::toHFOV (float fov, float aspect){
    return 2 * std::atan(std::tan(fov/2) / aspect);
}

float glMath::toYFOV (float fov, float aspect){
    return 2 * std::atan(std::tan(fov/2) * aspect);
}

float glMath::toPower (float intensity){
    return 4 * M_PI * intensity / LUMENS_PER_WATT;
}

int glMath::sign(float n) {
    return std::signbit(n) == 1 ? -1 : 1;
}