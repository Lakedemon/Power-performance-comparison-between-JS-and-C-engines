//
// Created by leoni on 23/03/2023.
//

#include "PointLight.h"

PointLight::PointLight(Vector3 color, float power): color(color), intensity(power) {}
PointLight::PointLight() : PointLight(Vector3::one, 1){}

Vector3 PointLight::scaledColor() const {
    return color.normalized() * intensity;
}
