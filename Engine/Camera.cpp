#include "Camera.h"

Camera::Camera(float fov, float aspect, float near, float far) : _fov(fov), _aspect(aspect), _near(near), _far(far){
    this->projectionMatrix = Matrix4::perspective(glMath::toRad(fov), aspect, near, far);
}

Camera::Camera(const Camera &camera) : Camera(camera._fov, camera._aspect, camera._near, camera._far){
    this->transform = {camera.transform};
}

Camera::Camera() : Camera(1, 1, 0.001, 100) {}

Matrix4 Camera::viewMat() {
    return {transform, true};
}

void Camera::resetProjection() {
    this->projectionMatrix = Matrix4::perspective(glMath::toRad(this->_fov),this->_aspect, this->_near,this->_far);
}

Vector4 Camera::clippingPlane(const Transform& plane, Matrix4 viewMat, int side) {
    const Vector3 pos = viewMat * plane.position;
    const Vector3 normal = ((viewMat.multiplyVector(plane.forward())) * (float)side).normalized();

    const float dis = -Vector3::dot(pos, normal);
    return {normal.x, normal.y, normal.z, dis};
}

Matrix4 Camera::relativeMirror(const Matrix4& from, Matrix4 to) {
    return this->viewMat() * from * (Matrix4::identity().rotateY(glMath::toRad(180))) * to.inverse();
}

