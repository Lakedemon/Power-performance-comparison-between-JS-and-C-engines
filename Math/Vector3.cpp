#include "Vector3.h"

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized() const {
    const float length = magnitude();
    if (length < glMath::EPSILON){
        return zero;
    }

    return *this * (1/length);
}

Vector3 Vector3::one = {1, 1, 1};
Vector3 Vector3::zero = {0, 0, 0};
Vector3 Vector3::up = {0, 1, 0};
Vector3 Vector3::down = {0, -1, 0};
Vector3 Vector3::left = {-1, 0, 0};
Vector3 Vector3::right = {1, 0, 0};
Vector3 Vector3::forward = {0, 0, 1};
Vector3 Vector3::back = {0, 0, -1};

int Vector3::side(Vector3 depended, Vector3 control, Vector3 normal) {
    return std::signbit(dot(depended - control, normal));
}

float Vector3::angle(Vector3 a, Vector3 b) {
    const float mag = (a.magnitude() * b.magnitude());
    if(mag < glMath::EPSILON){return 0;}
    return std::acos(dot(a, b) / mag);
}

float Vector3::dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector3::distance(Vector3 a, Vector3 b) {
    return (a - b).magnitude();
}

Vector3 Vector3::cross(Vector3 a, Vector3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

Vector3 Vector3::QuaternionToEuler(float qx, float qy, float qz, float qw) {
    const float x = -atan2(
            2.0 * (qw * qx + qy * qz),
            1.0 - 2.0 * (qx * qx + qy * qy)
    );

    const float y = std::asin(
            glMath::clampUnit(2 * (qw * qy - qz * qx))
    );

    const float z = std::atan2(
            2 * (qw * qz + qx * qy),
            1 - 2 * (qy * qy + qz * qz)
    );

    return {x, y, z};
}

Vector3 Vector3::operator+(const Vector3 &b) const {
    return {x + b.x, y + b.y, z + b.z};
}
Vector3 Vector3::operator-(const Vector3 &b) const {
    return {x - b.x, y - b.y, z - b.z};
}
Vector3 Vector3::operator*(const Vector3 &b) const {
    return {x * b.x, y * b.y, z * b.z};
}
Vector3 Vector3::operator*(const float &b) const {
    return {x * b, y * b, z * b};
}
Vector3 Vector3::operator/(const float &b) const {
    return {x / b, y / b, z / b};
}
