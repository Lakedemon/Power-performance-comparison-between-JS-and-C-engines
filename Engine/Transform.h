#ifndef OPENGLENGINE_TRANSFORM_H
#define OPENGLENGINE_TRANSFORM_H

#include "../Math/glMath.h"
#include "../Math/Vector3.h"

struct Transform {
private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
public:
    Transform(Vector3 &position, Vector3 rotation, Vector3 scale);

    Transform copy();
    Vector3 forward();
    Vector3 forward2D();
    Vector3 back();
    Vector3 back2D();
    Vector3 left();
    Vector3 right();
    Vector3 up();
    Vector3 down();
};


#endif //OPENGLENGINE_TRANSFORM_H
