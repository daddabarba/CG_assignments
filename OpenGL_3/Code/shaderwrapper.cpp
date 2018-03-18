#include "shaderwrapper.h"

void shaderWrapper::create(const char*pathVert, const char *pathFrag){
    addShaderFromSourceFile(QOpenGLShader::Vertex, pathVert);
    addShaderFromSourceFile(QOpenGLShader::Fragment, pathFrag);

    link();

    getUniLoc();
}

void shaderWrapper::getUniLoc()
{
    uniformModel      = uniformLocation("modelTransform");
    uniformProjection = uniformLocation("projection");
    uniformView       = uniformLocation("viewTransform");
    uniformViewNormal = uniformLocation("viewTransformNormal");
    uniformNormal     = uniformLocation("normalMatrix");

    uniformCameraPos = uniformLocation("cameraPos");
    uniformLightPos = uniformLocation("lightPos");
    uniformLightCol = uniformLocation("lightCol");
    uniformObjCol   = uniformLocation("objCol");
    uniformMaterial = uniformLocation("material");
    uniformSampler = uniformLocation("sampler");

    uniformAmplitudes = uniformLocation("amplitude");
    uniformPhases = uniformLocation("phi");
    uniformFrequencies = uniformLocation("omega");
    uniformNWaves = uniformLocation("num_waves");
    uniformTime = uniformLocation("time");
}
