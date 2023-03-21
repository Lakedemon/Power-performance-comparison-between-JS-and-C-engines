#include "Vector2.h"

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const {
    float length = magnitude();
    if (length < glMath::EPSILON){
        return zero;
    }

    float lengthInv = 1 / length;
    return {x * lengthInv, y * lengthInv};
}

Vector2 Vector2::one = {1, 1};
Vector2 Vector2::zero = {0, 0};
Vector2 Vector2::up = {0, 1};
Vector2 Vector2::down = {0, -1};
Vector2 Vector2::left = {-1, 0};
Vector2 Vector2::right = {1, 0};

int Vector2::side(Vector2 depended, Vector2 control, Vector2 normal) {
    return std::signbit(dot(depended - control, normal));
}

float Vector2::distance(Vector2 a, Vector2 b) {
    return (a - b).magnitude();
}

float Vector2::angle(Vector2 a, Vector2 b) {
    float mag = (a.magnitude() * b.magnitude());
    if(mag < glMath::EPSILON){return 0;}
    return std::acos(dot(a, b) / mag);
}

float Vector2::dot(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

float Vector2::cross(Vector2 a, Vector2 b) {
    return a.x * b.y - a.y * b.y;
}
Vector2 Vector2::operator+(const Vector2 &b) const {
    return {x + b.x, y + b.y};
}
Vector2 Vector2::operator-(const Vector2 &b) const {
    return {x - b.x, y - b.y};
}
Vector2 Vector2::operator*(const Vector2 &b) const {
    return {x * b.x, y * b.y};
}
Vector2 Vector2::operator*(const float &b) const {
    return {x * b, y * b};
}

Vector2 Vector2::operator/(const float &b) const {
    return {x / b, y / b};
}
