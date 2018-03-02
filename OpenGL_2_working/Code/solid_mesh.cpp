#include "solid_mesh.h"

solid_mesh::solid_mesh(const char* file)
{
    Model mesh_solid(file); //Loading mesh from file
    QVector <QVector3D> solid_vertices = mesh_solid.getVertices(); //Storing QVEctor of QVector3D (vertices' locations)
    QVector <QVector3D> solid_normals  = mesh_solid.getNormals();

    size_solid = solid_vertices.length();       //Getting number of vertices

    QVector3D *vertices = solid_vertices.data(); //Getting array of QVector3D (vertices' locations)
    QVector3D *normals  = solid_normals.data();

    figure_solid = (vertex *)malloc(size_solid*sizeof(vertex));  //Allocating array of vertices (as defined in geoms.h)

    for(int i=0; i<size_solid; i++){ //for every vertex
        //take position
        point p = set_point(vertices[i].x(), vertices[i].y(), vertices[i].z());
        //generate RGB color from normals
        //RGB_color col = set_color(normals[i].x()*0.5 + 0.5, normals[i].y()*0.5 + 0.5, normals[i].z()*0.5 + 0.5);
        RGB_color col = set_color(normals[i].x(), normals[i].y(), normals[i].z());

        //Store vertex (as defined in geoms.h)
        figure_solid[i] = set_vertex(p,col);

    }
}

QMatrix3x3 solid_mesh::getNormalMatrix(){
    return (transformation.getMatrix()).normalMatrix();
}

void solid_mesh::discard_vertices(){
    free(figure_solid);
}
