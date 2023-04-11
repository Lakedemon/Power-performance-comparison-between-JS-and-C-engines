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

/*static std::map<int, > = {
        5120: Int8Array,
        5121: Uint8Array,
        5122: Int16Array,
        5123: Uint16Array,
        5125: Uint32Array,
        5126: Float32Array,
}*/