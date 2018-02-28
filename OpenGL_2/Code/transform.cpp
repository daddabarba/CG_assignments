#include "transform.h"

//Initial transformation Identity matrix (no rotation, translation or scaling)
Transform::Transform() {
    posX = posY = posZ = rotX = rotY = rotZ = 0.0f;
    scale = 1.0f;
}

//Updating x,y, and z translation according to given values
void Transform::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

//Updating x,y, and z rotation according to given values
void Transform::setRotation(float x, float y, float z) {
    rotX = x;
    rotY = y;
    rotZ = z;
}

//Updating (uniform) scaling according to given value
void Transform::setScale(float s) {
    scale = s;
}

//Generating QMAtrix4x4 according to tranformation
QMatrix4x4 Transform::getMatrix() {
    QMatrix4x4 t; //Setting matrix

    t.translate(posX, posY, posZ); //Setting x,y, and z translation
    t.rotate(rotX, 1, 0, 0); //x rotation (around x axis)
    t.rotate(rotY, 0, 1, 0); //y rotation (around y axis)
    t.rotate(rotZ, 0, 0, 1); //z rotation (around z axis)
    t.scale(scale);  //Setting uniform scaling

    return t;
}
