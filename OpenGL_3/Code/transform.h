#ifndef TRANSFORM
#define TRANSFORM

#include <QMatrix4x4>
#include "geoms.h"

class Transform { //A class to wrap a QMatrix4x4 matrix for easy model transformation storage
public:
    float posX, posY, posZ; //Translation vector
    float rotX, rotY, rotZ; //Rotation vector
    float scale;            //(uniform) scaling factor

    Transform();

    void setPosition(float x, float y, float z); //change translation
    void setRotation(float x, float y, float z); //change rotation
    void setScale(float s);                      //change (uniform) scaling

    QMatrix4x4 getMatrix();   //generate QMatrix4x4 applying the above defined tranformation

    Transform operator+(const Transform &t) const;
};

class TurntableTransform : public Transform {
public:
    TurntableTransform();
    point target;
    QVector3D getCameraPosition();
    QMatrix4x4 getMatrix();
};

#endif // TRANSFORM

