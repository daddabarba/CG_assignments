#ifndef SOLID_MESH_H
#define SOLID_MESH_H

#include "geoms.h"
#include "transform.h"

#include "model.h"

#include <QOpenGLShaderProgram>
#include <QVector3D>

class solid_mesh
{
public:
    solid_mesh(const char* file);

    QMatrix3x3 getNormalMatrix();

    void discard_vertices();

    Transform transformation;
    GLuint VAO, VBO;
    int size_solid;

    vertex *figure_solid;

};

#endif // SOLID_MESH_H
