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
    uniformNormal     = uniformLocation("normalMatrix");

    uniformLightPos = uniformLocation("lightPos");
    uniformLightCol = uniformLocation("lightCol");
    uniformObjCol   = uniformLocation("objCol");
    uniformMaterial = uniformLocation("material");
    uniformSampler = uniformLocation("sampler");
}

