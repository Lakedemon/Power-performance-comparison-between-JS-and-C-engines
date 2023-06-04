#ifndef OPENGLENGINE_CAMERA_H
#define OPENGLENGINE_CAMERA_H


#include "EmptyObject.h"
#include "../Math/Matrix4.h"

class Camera : public EmptyObject {
private:
    float _fov;
    float _aspect;
    float _near;
    float _far;
public:
    Camera(float fov, float aspect, float near, float far);
    Camera(const Camera& camera);
    Camera();
    Matrix4 viewMat();
    Matrix4 projectionMatrix;
    void resetProjection();
    static Vector4 clippingPlane(const Transform& plane, Matrix4 viewMat, int side);
    Matrix4 relativeMirror(const Matrix4& from, Matrix4 to);
};


#endif //OPENGLENGINE_CAMERA_H
