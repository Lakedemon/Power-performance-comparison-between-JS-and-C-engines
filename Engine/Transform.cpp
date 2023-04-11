#include "Transform.h"

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale){}
Transform::Transform(const Transform& transform) : Transform(transform.position, transform.rotation, transform.scale){}
Transform::Transform() : Transform(Vector3::zero,Vector3::zero,Vector3::one){}

void Transform::copy(const Transform& transform) {
    this->position = transform.position;
    this->rotation = transform.rotation;
    this->scale = transform.scale;
}

Matrix4 Transform::worldMatrix() {
    return Matrix4{*this, false};
}

Vector3 Transform::forward() const {
    const float x = rotation.x;
    const float y = rotation.x;

    const float c = std::cos(y);
    Vector3 v = {-std::sin(y), c * std::sin(x), c * std::cos(x)};
    return v.normalized();
}

Vector3 Transform::forward2D() const {
    const float x = rotation.x;
    const float y = rotation.x;

    const float c = std::cos(y);
    Vector3 v = {-std::sin(y), 0, c * std::cos(x)};
    return v.normalized();
}

Vector3 Transform::back() const {
    return -forward();
}

Vector3 Transform::back2D() const {
    return -forward2D();
}

Vector3 Transform::left() const {
    const float y = rotation.y;
    return {std::cos(y),0, std::sin(y)};
}

Vector3 Transform::right() const {
    return -left();
}

Vector3 Transform::up() const {
    const float x = rotation.x;
    const float y = rotation.x;

    const float s = std::sin(y);
    Vector3 v = {std::cos(y), /*s * Math.cos(x)*/0, s * std::cos(x)};
    return v.normalized();
}

Vector3 Transform::down() const {
    return -up();
}
