//
// Created by leoni on 19/03/2023.
//

#include "PBRMetallicRoughness.h"

PBRMetallicRoughness::PBRMetallicRoughness(Vector3 baseColor, float roughness, float metallic) : baseColor(Vector3::one) {
    this->baseColor = baseColor;
    this->roughness = roughness;
    this->metallic = metallic;
}

PBRMetallicRoughness PBRMetallicRoughness::defaultMaterial() {
    return PBRMetallicRoughness();
}
