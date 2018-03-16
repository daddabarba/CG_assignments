#include "geoms.h"

#include <cmath>

RGB_color set_color(float r, float g, float b){//Given red, blue and green values, return a RGB_color struct
    RGB_color ret;

    ret.r = r;
    ret.g = g;
    ret.b = b;

    return ret;
}

phong_mat set_material(float a, float d, float s, float e){//Given ambient, diffuse, specular and exponent, return a phong_mat struct
    phong_mat ret;

    ret.a = a;
    ret.d = d;
    ret.s = s;
    ret.e = e;

    return ret;
}

coord set_coord(float x, float y){//Given x and y values, return a coord struct
    coord ret;

    ret.x = x;
    ret.y = y;

    return ret;
}

point set_point(float x, float y, float z){//Given x, y and z coordinates, return a point struct
    point ret;

    ret.x = x;
    ret.y = y;
    ret.z = z;

    return ret;
}

vertex set_vertex(point position, RGB_color color){//Given a point and a color returns a vector struct
    vertex ret;

    ret.position = position;
    ret.color = color;

    return ret;
}

vertex set_vertex(point position, RGB_color color, coord texcoord){//Given a point and a color returns a vector struct
    vertex ret;

    ret.position = position;
    ret.color = color;
    ret.texcoord = texcoord;

    return ret;
}

triangle set_triangle(vertex v1, vertex v2, vertex v3){//Given three vertices, defining a triangle
    triangle ret;

    ret.v1 = v1;
    ret.v2 = v2;
    ret.v3 = v3;

    return ret;
}

//Given side length l, and 8 vertices' colors, generates a cube with side long l, centered in the origin
cube set_cube(float side_length, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5, RGB_color c6, RGB_color c7, RGB_color c8 ){
    cube ret;
    float l = side_length/2;

    //Computing 8 vertices
    vertex v1 = set_vertex(set_point( l, l, l), c1); //x>0, y>0, z>0
    vertex v2 = set_vertex(set_point( l, l,-l), c2); //x>0, y>0, z<0
    vertex v3 = set_vertex(set_point( l,-l, l), c3); //x>0, y<0, z>0
    vertex v4 = set_vertex(set_point( l,-l,-l), c4); //x>0, y<0, z<0
    vertex v5 = set_vertex(set_point(-l, l, l), c5); //x<0, y>0, z>0
    vertex v6 = set_vertex(set_point(-l, l,-l), c6); //x<0, y>0, z<0
    vertex v7 = set_vertex(set_point(-l,-l, l), c7); //x<0, y<0, z>0
    vertex v8 = set_vertex(set_point(-l,-l,-l), c8); //x<0, y<0, z<0


    //Defining all 12 triangles (given the 8 vertices)
    ret.f11 = set_triangle(v7,v3,v5);
    ret.f12 = set_triangle(v5,v3,v1);
    ret.f21 = set_triangle(v3,v4,v1);
    ret.f22 = set_triangle(v4,v2,v1);
    ret.f31 = set_triangle(v2,v4,v8);
    ret.f32 = set_triangle(v8,v6,v2);
    ret.f41 = set_triangle(v6,v8,v7);
    ret.f42 = set_triangle(v6,v7,v5);
    ret.f51 = set_triangle(v5,v1,v6);
    ret.f52 = set_triangle(v1,v2,v6);
    ret.f61 = set_triangle(v8,v4,v7);
    ret.f62 = set_triangle(v7,v4,v3);

    return ret;
}

//given base side length l height h, and 5 vertices' colors, generates a pyramid centerd in the origin
pyramid set_pyramid(float side_length, float height, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5 ){
    pyramid ret;
    float l = side_length/2, h = height/2;

    //Computing 5 vertices (base parallel to xz plane)
    vertex v1 = set_vertex(set_point(  l,-h,   l), c1); //x>, z>0
    vertex v2 = set_vertex(set_point(  l,-h,  -l), c2); //x>, z<0
    vertex v3 = set_vertex(set_point( -l,-h,   l), c3); //x<, z>0
    vertex v4 = set_vertex(set_point( -l,-h,  -l), c4); //x<, z<0
    vertex v5 = set_vertex(set_point(0.0, h, 0.0), c5); //top vertex on y axis

    //Defining all 6 triangles (given the 5 vertices)
    ret.b1 = set_triangle(v2,v1,v3); //Base first half
    ret.b2 = set_triangle(v2,v3,v4); //Base second half
    ret.f1 = set_triangle(v3,v1,v5); //Side face 1
    ret.f2 = set_triangle(v1,v2,v5); //Side face 2
    ret.f3 = set_triangle(v2,v4,v5); //Side face 3
    ret.f4 = set_triangle(v4,v3,v5); //Side face 4

    return ret;
}

double point_distance(point p){
    return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}

point scale_point(point p, double factor){
    return set_point(p.x*factor, p.y*factor, p.z*factor);
}

point add_point(point p, point t){
    return set_point(p.x+t.x, p.y+t.y, p.z+t.z);
}
