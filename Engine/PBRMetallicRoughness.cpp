#include "PBRMetallicRoughness.h"

PBRMetallicRoughness::PBRMetallicRoughness(Vector3 baseColor, float roughness, float metallic) : baseColor(baseColor), roughness(roughness), metallic(metallic) {}
PBRMetallicRoughness::PBRMetallicRoughness() : PBRMetallicRoughness(Vector3::one, 0.5, 0){}

void PBRMetallicRoughness::useMaterial(Shader &shader) const {
    glUniform3f(glGetUniformLocation(shader.getId(), "baseColor"), baseColor.x, baseColor.y, baseColor.z);
    glUniform1f(glGetUniformLocation(shader.getId(), "roughness"), roughness);
    glUniform1f(glGetUniformLocation(shader.getId(), "metallic"), metallic);
}
