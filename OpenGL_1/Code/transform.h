#ifndef TRANSFORM
#define TRANSFORM

#include <QMatrix4x4>

class Transform {
public:
    float posX, posY, posZ;
    float rotX, rotY, rotZ;
    float scale;

    Transform();
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setScale(float s);
    QMatrix4x4 getMatrix();
};

#endif // TRANSFORM

