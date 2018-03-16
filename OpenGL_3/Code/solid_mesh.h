#ifndef SOLID_MESH_H
#define SOLID_MESH_H

#include "geoms.h"
#include "transform.h"

#include "colors.h"

#include "model.h"
#include "animation.h"

#include <QOpenGLShaderProgram>
#include <QVector3D>

class solid_mesh
{
public:
    solid_mesh(const char* file, point positon, float scale, RGB_color col=blue, phong_mat kPar=set_material(1.0,1.0,1.0,16));

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

    GLuint tex;

    RGB_color color;
    phong_mat material;

    vertex *figure_solid;

    animation anim;
    void animate();

};

#endif // SOLID_MESH_H
