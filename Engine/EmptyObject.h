#ifndef OPENGLENGINE_EMPTYOBJECT_H
#define OPENGLENGINE_EMPTYOBJECT_H

#include "Transform.h"

class EmptyObject {
private:
    Transform transform;
public:
    EmptyObject();
    ~EmptyObject();
    void setPosition(Vector3 v);
    void setRotation(Vector3 v);
    void setScale(Vector3 v);
};


#endif //OPENGLENGINE_EMPTYOBJECT_H
