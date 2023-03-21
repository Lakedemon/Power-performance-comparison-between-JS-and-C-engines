//
// Created by leoni on 19/03/2023.
//

#ifndef OPENGLENGINE_PBRMETALLICROUGHNESS_H
#define OPENGLENGINE_PBRMETALLICROUGHNESS_H

#include "../Math/Vector3.h"

class PBRMetallicRoughness {
private:
    Vector3 baseColor;
    float roughness, metallic;
public:
    explicit PBRMetallicRoughness(Vector3 baseColor = Vector3::one, float roughness = 0.5, float metallic = 0);
    static PBRMetallicRoughness defaultMaterial();
    void useMaterial();
};

#endif //OPENGLENGINE_PBRMETALLICROUGHNESS_H
