#ifndef OPENGLENGINE_TRANSFORM_H
#define OPENGLENGINE_TRANSFORM_H

#include "../Math/glMath.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"

class Matrix4;
struct Transform {
public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Transform(Vector3 position, Vector3 rotation, Vector3 scale);
    Transform(const Transform& transform);
    Transform();

    void copy(const Transform& transform);

    Matrix4 worldMatrix();
    [[nodiscard]] Vector3 forward() const;
    [[nodiscard]] Vector3 forward2D() const;
    [[nodiscard]] Vector3 back() const;
    [[nodiscard]] Vector3 back2D() const;
    [[nodiscard]] Vector3 left() const;
    [[nodiscard]] Vector3 right() const;
    [[nodiscard]] Vector3 up() const;
    [[nodiscard]] Vector3 down() const;
};


#endif //OPENGLENGINE_TRANSFORM_H
