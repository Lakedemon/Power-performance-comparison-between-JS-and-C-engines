#ifndef OPENGLENGINE_EMPTYOBJECT_H
#define OPENGLENGINE_EMPTYOBJECT_H

#include "Transform.h"

struct EmptyObject {
public:
    Transform transform;

    EmptyObject();
    Matrix4 worldMatrix();
    void setPosition(Vector3 v);
    void setRotation(Vector3 v);
    void setScale(Vector3 v);
};


#endif //OPENGLENGINE_EMPTYOBJECT_H
