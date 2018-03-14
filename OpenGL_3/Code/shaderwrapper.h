#ifndef SHADERWRAPPER_H
#define SHADERWRAPPER_H

#include <QOpenGLShaderProgram>

#include "geoms.h"

class shaderWrapper: public QOpenGLShaderProgram
{
public:
    void create(const char *pathVert, const char *pathFrag);

    GLint uniformModel;
    GLint uniformProjection;
    GLint uniformView;
    GLint uniformViewNormal;
    GLint uniformNormal;

    GLint uniformCameraPos;
    GLint uniformLightPos;
    GLint uniformLightCol;
    GLint uniformObjCol;
    GLint uniformMaterial;
    GLint uniformSampler;

    void sendMaterial(RGB_color kPar);
    void sendObjectCol(RGB_color color);
    void sendLight(vertex light);

private:
    void getUniLoc();
};

#endif // SHADERWRAPPER_H
