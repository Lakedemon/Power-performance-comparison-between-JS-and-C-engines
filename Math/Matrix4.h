#ifndef OPENGLENGINE_MATRIX4_H
#define OPENGLENGINE_MATRIX4_H

#include "glMath.h"
#include "Vector3.h"
#include "Vector4.h"
#include "../Engine/Transform.h"
#include <cmath>

class Transform;
struct Matrix4 {
private:
    static Matrix4 translation(Vector3 &v);
    static Matrix4 scalation(Vector3 &v);
    static Matrix4 rotationX(float r);
    static Matrix4 rotationY(float r);
    static Matrix4 rotationZ(float r);
    void copyEntries(const float entriesToCopy[16]);
    void copyEntries(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20,
                     float _21, float _22, float _23, float _30, float _31, float _32, float _33);
public:
    float entries[16]{};
    Matrix4(float _00, float _01, float _02, float _03,
            float _10, float _11, float _12, float _13,
            float _20, float _21, float _22, float _23,
            float _30, float _31, float _32, float _33);
    Matrix4(Transform &transform, bool inverse);
    Matrix4(const float entries[16]);
    Matrix4(Matrix4& matrix4);

    Matrix4();
    Vector3 position();
    Vector3 size();
    Vector3 rotation();

    Matrix4 inverse();
    Matrix4 transpose();
    void setRow(int n, Vector4 &v);
    Vector4 getRow(int n);

    void setColumn(int n, Vector4 v);
    Vector4 getColumn(int n);
    static Matrix4 identity();
    static Matrix4 zero();
    static Matrix4 perspective(float fov, float aspect, float near, float far);

    static Matrix4 lookAt(Vector3 &eye, Vector3 &target, Vector3 &up);
    void clipProjectionMatrix(Vector4 clipPlane);

    void clipRevProjectionMatrix(Vector4 clipPlane);
    Matrix4 rotateX(float r);
    Matrix4 rotateY(float r);
    Matrix4 rotateZ(float r);
    Matrix4 translate(Vector3 &v);
    Matrix4 rotate(Vector3 &v);

    Matrix4 scale(Vector3 &v);
    Vector3 multiplyVector(Vector3 v);
    Matrix4 operator*(const Matrix4 &b);
    Matrix4& operator=(const Matrix4 &b);
    Matrix4& operator*=(const Matrix4 &b);
    Vector4 operator*(const Vector4 &v);
    Vector3 operator*(const Vector3 &v);

    explicit operator Transform();
};


#endif //OPENGLENGINE_MATRIX4_H
