#include "solid_mesh.h"

solid_mesh::solid_mesh(const char* file, point position, float scale, RGB_color col, phong_mat kPar)
{
    base_scale = scale;
    base_translation = position;

    color = col;
    material = kPar;

    Model mesh_solid(file); //Loading mesh from file
    QVector <QVector3D> solid_vertices = mesh_solid.getVertices(); //Storing QVEctor of QVector3D (vertices' locations)
    QVector <QVector3D> solid_normals  = mesh_solid.getNormals();
    QVector <QVector2D> solid_texCoords = mesh_solid.getTextureCoords();

    size_solid = solid_vertices.length();       //Getting number of vertices

    QVector3D *vertices = solid_vertices.data(); //Getting array of QVector3D (vertices' locations)
    QVector3D *normals  = solid_normals.data();
    QVector2D *texCoords  = solid_texCoords.data();

    figure_solid = (vertex *)malloc(size_solid*sizeof(vertex));  //Allocating array of vertices (as defined in geoms.h)

    for(int i=0; i<size_solid; i++){ //for every vertex
        //take position
        point p = set_point(vertices[i].x(), vertices[i].y(), vertices[i].z());
        //generate RGB color from normals
        RGB_color col = set_color(normals[i].x(), normals[i].y(), normals[i].z());

        coord texCoord = set_coord(texCoords[i].x(), texCoords[i].y());

        //Store vertex (as defined in geoms.h)
        figure_solid[i] = set_vertex(p,col,texCoord);

    }

    setPosition(position.x,position.y,position.z);
    setScale(1.0f);
}

//Updating x,y, and z translation according to given values
void solid_mesh::setPosition(float x, float y, float z) {
    transformation.setPosition(x,y,z);
}

//Updating x,y, and z rotation according to given values
void solid_mesh::setRotation(float x, float y, float z) {
    transformation.setRotation(x,y,z);
}

//Updating (uniform) scaling according to given value
void solid_mesh::setScale(float s) {
    transformation.setScale(s*base_scale);
}


QMatrix3x3 solid_mesh::getNormalMatrix(){
    return (transformation.getMatrix()).normalMatrix();
}

void solid_mesh::discard_vertices(){
    free(figure_solid);
}
