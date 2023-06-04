#include "EmptyObject.h"

EmptyObject::EmptyObject(){
    this->transform = {};
}

Matrix4 EmptyObject::worldMatrix() {
    return this->transform.worldMatrix();
}

void EmptyObject::setPosition(Vector3 v) {
    this->transform.position = v;
}

void EmptyObject::setRotation(Vector3 v) {
    this->transform.rotation = v;
}

void EmptyObject::setScale(Vector3 v) {
    this->transform.scale = v;
}
