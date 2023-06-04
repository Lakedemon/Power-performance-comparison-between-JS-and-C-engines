#ifndef OPENGLENGINE_POINTLIGHT_H
#define OPENGLENGINE_POINTLIGHT_H


#include "../Math/Vector3.h"
#include "EmptyObject.h"

struct PointLight : public EmptyObject{
    Vector3 color;
    float intensity;

    PointLight(Vector3 color, float power);
    PointLight();
    [[nodiscard]] Vector3 scaledColor() const;
};


#endif //OPENGLENGINE_POINTLIGHT_H
