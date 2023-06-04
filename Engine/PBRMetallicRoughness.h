#ifndef OPENGLENGINE_PBRMETALLICROUGHNESS_H
#define OPENGLENGINE_PBRMETALLICROUGHNESS_H

#include "../Math/Vector3.h"
#include "../GL_Helpers/Shader.h"

class PBRMetallicRoughness {
private:
    Vector3 baseColor;
    float roughness, metallic;
public:
    PBRMetallicRoughness(Vector3 baseColor, float roughness, float metallic);
    PBRMetallicRoughness();
    void useMaterial(Shader& shader) const;
};

#endif //OPENGLENGINE_PBRMETALLICROUGHNESS_H
