#ifndef SOLID_MESH_H
#define SOLID_MESH_H

#include "geoms.h"
#include "transform.h"

#include "colors.h"

#include "model.h"

#include <QOpenGLShaderProgram>
#include <QVector3D>

class solid_mesh
{
public:
    solid_mesh(const char* file, point positon, float scale, RGB_color col=blue, RGB_color kPar=set_color(1.0,1.0,1.0));

    QMatrix3x3 getNormalMatrix();

    void discard_vertices();

    Transform transformation;
    float base_scale;
    point base_translation;

    void setPosition(float x, float y, float z); //change translation
    void setRotation(float x, float y, float z); //change rotation
    void setScale(float s);                      //change (uniform) scaling

    GLuint VAO, VBO;
    int size_solid;

    RGB_color color, material;

    vertex *figure_solid;

};

#endif // SOLID_MESH_H
