#ifndef OPENGLENGINE_OBJECT3D_H
#define OPENGLENGINE_OBJECT3D_H

#include "Mesh.h"
#include "EmptyObject.h"
#include "PBRMetallicRoughness.h"
#include "../GL_Helpers/Shader.h"

class Object3D : public EmptyObject{
private:
    PBRMetallicRoughness material;
    Shader shader;
public:
    unsigned int tag;

    Object3D(Mesh mesh, Shader shader, PBRMetallicRoughness material, unsigned int tag = Tags::def);
    Object3D() = default;
    void updateUniforms();
    void drawObject();
    enum Tags {
            def = 0,
            portal = 1
    };
    Mesh mesh;
};


#endif //OPENGLENGINE_OBJECT3D_H
