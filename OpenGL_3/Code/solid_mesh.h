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
    solid_mesh();
    solid_mesh(const char* file, point positon, float scale, phong_mat kPar=set_material(1.0,1.0,1.0,16));

    QMatrix3x3 getNormalMatrix();

    void discard_vertices();

    Transform transformation;
    float base_scale;
    point base_translation;

    void setPosition(float x, float y, float z); //change translation
    void setRotation(float x, float y, float z); //change rotation
    void setScale(float s);                      //change (uniform) scaling

    GLuint VAO, VBO;
    int size_solid; //number of vertices

    GLuint tex; //texture location

    RGB_color color;
    phong_mat material;

    vertex *figure_solid;

    animation anim; //animation
    void animate(); //apply animation to object model transform

};

#endif // SOLID_MESH_H
