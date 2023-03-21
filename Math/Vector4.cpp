#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w){
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
};

[[nodiscard]] float Vector4::magnitude() const{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

[[nodiscard]] Vector4 Vector4::normalized() const{
    float length = magnitude();
    if (length < glMath::EPSILON){
        return zero;
    }
    return *this * (1 / length);
}

Vector4 Vector4::one = {1, 1, 1, 1};
Vector4 Vector4::zero = {0, 0, 0, 0};

float Vector4::angle(Vector4 a, Vector4 b) {
    const float mag = (a.magnitude() * b.magnitude());
    if (mag < glMath::EPSILON) return 0;

    return std::acos(Vector4::dot(a, b) / mag);
}

float Vector4::dot(Vector4 a, Vector4 b){
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4 Vector4::operator+(const Vector4 &b) const {
    return {x + b.x, y + b.y, z + b.z, w + b.w};
}

Vector4 Vector4::operator-(const Vector4 &b) const {
    return {x - b.x, y - b.y, z - b.z, w - b.w};
}

Vector4 Vector4::operator*(const Vector4 &b) const {
    return {x * b.x, y * b.y, z * b.z, w * b.w};
}

Vector4 Vector4::operator*(const float &b) const {
    return {x * b, y * b, z * b, w * b};
}

Vector4 Vector4::operator/(const float &b) const {
    return {x / b, y / b, z / b, w / b};
}

int Vector4::side(Vector4 depended, Vector4 control, Vector4 normal) {
    return 0;
}

float Vector4::distance(Vector4 a, Vector4 b) {
    return 0;
}
