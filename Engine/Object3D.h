#ifndef OPENGLENGINE_OBJECT3D_H
#define OPENGLENGINE_OBJECT3D_H

#include "Mesh.h"
#include "EmptyObject.h"
#include "PBRMetallicRoughness.h"
#include "../GL_Helpers/Shader.h"

class Object3D : EmptyObject{
private:
    Mesh mesh;
    PBRMetallicRoughness material;
    Shader shader;
public:
    Object3D(Mesh mesh, Shader shader, PBRMetallicRoughness material, unsigned int tag);
    void updateUniforms();
    void drawObject();
};


#endif //OPENGLENGINE_OBJECT3D_H
