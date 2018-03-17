#ifndef SHADERWRAPPER_H
#define SHADERWRAPPER_H

#include <QOpenGLShaderProgram>

#include "geoms.h"

class shaderWrapper: public QOpenGLShaderProgram
{
public:
    virtual void create(const char *pathVert, const char *pathFrag);

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
    virtual void getUniLoc();
};

class waveShaderWrapper: public shaderWrapper
{
public:
    void create(const char *pathVert, const char *pathFrag) override;

    GLint uniformAmplitudes;
    GLint uniformPhases;
    GLint uniformFrequencies;

    GLint uniformNWaves;

    GLint uniformTime;

private:
    void getUniLoc() override;
}

#endif // SHADERWRAPPER_H
