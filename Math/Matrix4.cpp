#include "Matrix4.h"

#include <cmath>

Matrix4::Matrix4(const float entries[16]) {
    for ( int i = 0; i < 16; ++i){
        this->entries[i] = entries[i];
    }
}

Matrix4::Matrix4(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20,
                 float _21, float _22, float _23, float _30, float _31, float _32, float _33) {
    this->entries[0] = _00;
    this->entries[1] = _01;
    this->entries[2] = _02;
    this->entries[3] = _03;
    this->entries[4] = _10;
    this->entries[5] = _11;
    this->entries[6] = _12;
    this->entries[7] = _13;
    this->entries[8] = _20;
    this->entries[9] = _21;
    this->entries[10] = _22;
    this->entries[11] = _23;
    this->entries[12] = _30;
    this->entries[13] = _31;
    this->entries[14] = _32;
    this->entries[15] = _33;
}

Matrix4 Matrix4::translation(Vector3 &v) {
    return {1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            v.x, v.y, v.z, 1};
}

Matrix4 Matrix4::scalation(Vector3 &v) {
    return {v.x, 0, 0, 0,
            0, v.y, 0, 0,
            0, 0, v.z, 0,
            0, 0, 0, 1};
}

Matrix4 Matrix4::rotationX(float r) {
    const float c = std::cos(r);
    const float s = std::sin(r);

    return {1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1};
}

Matrix4 Matrix4::rotationY(float r) {
    const float c = std::cos(r);
    const float s = std::sin(r);

    return {c, 0, s, 0,
            0, 1, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1};
}

Matrix4 Matrix4::rotationZ(float r) {
    const float c = std::cos(r);
    const float s = std::sin(r);

    return {c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
}

Vector3 Matrix4::position() {
    return {entries[12], entries[13], entries[14]};
}

Vector3 Matrix4::size() {
    return {
        Vector3(entries[0], entries[1], entries[2]).magnitude(),
        Vector3(entries[4], entries[5], entries[6]).magnitude(),
        Vector3(entries[8], entries[9], entries[10]).magnitude()
    };
}

Vector3 Matrix4::rotation() {
    const Vector3 size = Matrix4::size();

    float y = std::atan((-entries[8] * size.x)/(entries[10] * size.z));
    y = entries[10] < 0 && entries[8] > 0 ? y - M_PI : entries[10] < 0 && entries[8] < 0 ? y + M_PI : y;

    return {
            std::asin(entries[9] / size.y),
            y,
            std::atan(-entries[1] / entries[5])
    };
}

Matrix4 Matrix4::inverse() {
    float m00 = this->entries[0];
    float m01 = this->entries[1];
    float m02 = this->entries[2];
    float m03 = this->entries[3];
    float m10 = this->entries[4];
    float m11 = this->entries[5];
    float m12 = this->entries[6];
    float m13 = this->entries[7];
    float m20 = this->entries[8];
    float m21 = this->entries[9];
    float m22 = this->entries[10];
    float m23 = this->entries[11];
    float m30 = this->entries[12];
    float m31 = this->entries[13];
    float m32 = this->entries[14];
    float m33 = this->entries[15];

    float tmp0 = m22 * m33;
    float tmp1 = m32 * m23;
    float tmp2 = m12 * m33;
    float tmp3 = m32 * m13;
    float tmp4 = m12 * m23;
    float tmp5 = m22 * m13;
    float tmp6 = m02 * m33;
    float tmp7 = m32 * m03;
    float tmp8 = m02 * m23;
    float tmp9 = m22 * m03;
    float tmp10 = m02 * m13;
    float tmp11 = m12 * m03;
    float tmp12 = m20 * m31;
    float tmp13 = m30 * m21;
    float tmp14 = m10 * m31;
    float tmp15 = m30 * m11;
    float tmp16 = m10 * m21;
    float tmp17 = m20 * m11;
    float tmp18 = m00 * m31;
    float tmp19 = m30 * m01;
    float tmp20 = m00 * m21;
    float tmp21 = m20 * m01;
    float tmp22 = m00 * m11;
    float tmp23 = m10 * m01;

    float t0 = tmp0 * m11 + tmp3 * m21 + tmp4 * m31 - (tmp1 * m11 + tmp2 * m21 + tmp5 * m31);
    float t1 = tmp1 * m01 + tmp6 * m21 + tmp9 * m31 - (tmp0 * m01 + tmp7 * m21 + tmp8 * m31);
    float t2 = tmp2 * m01 + tmp7 * m11 + tmp10 * m31 - (tmp3 * m01 + tmp6 * m11 + tmp11 * m31);
    float t3 = tmp5 * m01 + tmp8 * m11 + tmp11 * m21 - (tmp4 * m01 + tmp9 * m11 + tmp10 * m21);
    float d = 1 / (m00 * t0 + m10 * t1 + m20 * t2 + m30 * t3);

    return {
            d * t0, d * t1, d * t2, d * t3,
            d * (tmp1 * m10 + tmp2 * m20 + tmp5 * m30 - (tmp0 * m10 + tmp3 * m20 + tmp4 * m30)),
            d * (tmp0 * m00 + tmp7 * m20 + tmp8 * m30 - (tmp1 * m00 + tmp6 * m20 + tmp9 * m30)),
            d * (tmp3 * m00 + tmp6 * m10 + tmp11 * m30 - (tmp2 * m00 + tmp7 * m10 + tmp10 * m30)),
            d * (tmp4 * m00 + tmp9 * m10 + tmp10 * m20 - (tmp5 * m00 + tmp8 * m10 + tmp11 * m20)),
            d * (tmp12 * m13 + tmp15 * m23 + tmp16 * m33 - (tmp13 * m13 + tmp14 * m23 + tmp17 * m33)),
            d * (tmp13 * m03 + tmp18 * m23 + tmp21 * m33 - (tmp12 * m03 + tmp19 * m23 + tmp20 * m33)),
            d * (tmp14 * m03 + tmp19 * m13 + tmp22 * m33 - (tmp15 * m03 + tmp18 * m13 + tmp23 * m33)),
            d * (tmp17 * m03 + tmp20 * m13 + tmp23 * m23 - (tmp16 * m03 + tmp21 * m13 + tmp22 * m23)),
            d * (tmp14 * m22 + tmp17 * m32 + tmp13 * m12 - (tmp16 * m32 + tmp12 * m12 + tmp15 * m22)),
            d * (tmp20 * m32 + tmp12 * m02 + tmp19 * m22 - (tmp18 * m22 + tmp21 * m32 + tmp13 * m02)),
            d * (tmp18 * m12 + tmp23 * m32 + tmp15 * m02 - (tmp22 * m32 + tmp14 * m02 + tmp19 * m12)),
            d * (tmp22 * m22 + tmp16 * m02 + tmp21 * m12 - (tmp20 * m12 + tmp23 * m22 + tmp17 * m02))
    };
}

Matrix4 Matrix4::copy() {
    return {entries};
}

Matrix4 Matrix4::transpose() {
    return {
            entries[0], entries[4], entries[8], entries[12],
            entries[1], entries[5], entries[9], entries[13],
            entries[2], entries[6], entries[10], entries[14],
            entries[3], entries[7], entries[11], entries[15],
    };
}

void Matrix4::setRow(int n, Vector4 &v) {
    entries[n*4] = v.x;
    entries[n*4 + 1] = v.y;
    entries[n*4 + 2] = v.z;
    entries[n*4 + 3] = v.w;
}

Vector4 Matrix4::getRow(int n) {
    return {
    entries[n*4],
    entries[n*4 + 1],
    entries[n*4 + 2],
    entries[n*4 + 3],
    };
}

void Matrix4::setColumn(int n, Vector4 v) {
    entries[n] = v.x;
    entries[n + 4] = v.y;
    entries[n + 8] = v.z;
    entries[n + 12] = v.w;
}

Vector4 Matrix4::getColumn(int n) {
    return {
    entries[n],
    entries[n + 4],
    entries[n + 8],
    entries[n + 12],
    };
}

const Matrix4 Matrix4::identity = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
const Matrix4 Matrix4::zero = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far) {
    const float f = tan(M_PI * 0.5 - 0.5 * fov);
    const float rangeInv = 1 / (near - far);

    return {
        f / aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (near + far) * rangeInv, -1,
        0, 0, 2 * far * near * rangeInv, 0
    };
}

Matrix4 Matrix4::lookAt(Vector3 &eye, Vector3 &target, Vector3 &up) {
    const Vector3 forward = (eye - target).normalized();
    const Vector3 right = Vector3::cross(up, forward).normalized();
    const Vector3 y = Vector3::cross(forward, right).normalized();

    return {
        right.x, right.y, right.z, 0,
        y.x, y.y, y.z, 0,
        forward.x, forward.y, forward.z, 0,
        eye.x, eye.y, eye.z, 1
    };
}

void Matrix4::clipProjectionMatrix(Vector4 clipPlane) {
    const Vector4 vcamera = Vector4(
        (std::signbit(clipPlane.x) - entries[8]) / entries[0],
        (std::signbit(clipPlane.y) - entries[9]) / entries[5],
        1,
        (entries[10] / entries[14])
    );
    const float n = -1 / Vector4::dot(clipPlane, vcamera);

    entries[2] = n * clipPlane.x;
    entries[6] = n * clipPlane.y;
    entries[10] = n * clipPlane.z + 1;
    entries[14] = n * clipPlane.w;
}

void Matrix4::clipRevProjectionMatrix(Vector4 clipPlane) {
    const Vector4 vcamera = Vector4(
        (std::signbit(clipPlane.x) - entries[8]) / entries[0],
        (std::signbit(clipPlane.y) - entries[9]) / entries[5],
        1,
        ((1 - entries[10]) / entries[14])
    );
    const float n = 1 / Vector4::dot(clipPlane, vcamera);

    entries[2] = n * clipPlane.x;
    entries[6] = n * clipPlane.y;
    entries[10] = n * clipPlane.z;
    entries[14] = n * clipPlane.w;
}

/*Todo
    Matrix4 Matrix4::rotateX(float r) {
        Matrix4 b = * this;
        return b * rotationX(r);
        return *this;
    }
    Matrix4 Matrix4::rotateY(float r) {
        return Matrix4(nullptr);
    }
    Matrix4 Matrix4::rotateZ(float r) {
        return Matrix4(nullptr);
    }
    Matrix4 Matrix4::translate(Vector3 &v) {
        return Matrix4(nullptr);
    }
    Matrix4 Matrix4::rotate(Vector3 &v) {
        return Matrix4(nullptr);
    }
    Matrix4 Matrix4::scale(Vector3 &v) {
        return Matrix4(nullptr);
    }
*/

Matrix4 Matrix4::operator*(Matrix4 &b) {
    float a00 = this->entries[0];
    float a01 = this->entries[1];
    float a02 = this->entries[2];
    float a03 = this->entries[3];
    float a10 = this->entries[4];
    float a11 = this->entries[5];
    float a12 = this->entries[6];
    float a13 = this->entries[7];
    float a20 = this->entries[8];
    float a21 = this->entries[9];
    float a22 = this->entries[10];
    float a23 = this->entries[11];
    float a30 = this->entries[12];
    float a31 = this->entries[13];
    float a32 = this->entries[14];
    float a33 = this->entries[15];

    float b00 = b.entries[0];
    float b01 = b.entries[1];
    float b02 = b.entries[2];
    float b03 = b.entries[3];
    float b10 = b.entries[4];
    float b11 = b.entries[5];
    float b12 = b.entries[6];
    float b13 = b.entries[7];
    float b20 = b.entries[8];
    float b21 = b.entries[9];
    float b22 = b.entries[10];
    float b23 = b.entries[11];
    float b30 = b.entries[12];
    float b31 = b.entries[13];
    float b32 = b.entries[14];
    float b33 = b.entries[15];

    return {
    b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30,
    b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31,
    b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32,
    b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33,
    b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30,
    b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31,
    b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32,
    b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33,
    b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30,
    b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31,
    b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32,
    b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33,
    b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30,
    b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31,
    b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32,
    b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33
    };
}

