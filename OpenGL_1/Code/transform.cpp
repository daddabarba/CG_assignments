#include "transform.h"

Transform::Transform() {
    posX = posY = posZ = rotX = rotY = rotZ = 0.0f;
    scale = 1.0f;
}

void Transform::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Transform::setRotation(float x, float y, float z) {
    rotX = x;
    rotY = y;
    rotZ = z;
}

void Transform::setScale(float s) {
    scale = s;
}

QMatrix4x4 Transform::getMatrix() {
    QMatrix4x4 t;
    t.translate(posX, posY, posZ);
    t.rotate(rotX, 1, 0, 0);
    t.rotate(rotY, 0, 1, 0);
    t.rotate(rotZ, 0, 0, 1);
    t.scale(scale);
    return t;
}
