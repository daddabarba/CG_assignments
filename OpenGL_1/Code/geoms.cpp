#include "geoms.h"

RGB_color set_color(float r, float g, float b){
    RGB_color ret;

    ret.r = r;
    ret.g = g;
    ret.b = b;

    return ret;
}

point set_point(float x, float y, float z){
    point ret;

    ret.x = x;
    ret.y = y;
    ret.z = z;

    return ret;
}

vertex set_vertex(point position, RGB_color color){
    vertex ret;

    ret.position = position;
    ret.color = color;

    return ret;
}

triangle set_traingle(vertex v1, vertex v2, vertex v3){
    triangle ret;

    ret.v1 = v1;
    ret.v2 = v2;
    ret.v3 = v3;

    return ret;
}

cube set_cube(float side_length, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5, RGB_color c6, RGB_color c7, RGB_color c8 ){
    cube ret;
    float l = side_length/2;

    vertex v1 = set_vertex(set_point( l, l, l), c1);
    vertex v2 = set_vertex(set_point( l, l,-l), c2);
    vertex v3 = set_vertex(set_point( l,-l, l), c3);
    vertex v4 = set_vertex(set_point( l,-l,-l), c4);
    vertex v5 = set_vertex(set_point(-l, l, l), c5);
    vertex v6 = set_vertex(set_point(-l, l,-l), c6);
    vertex v7 = set_vertex(set_point(-l,-l, l), c7);
    vertex v8 = set_vertex(set_point(-l,-l,-l), c8);


    ret.f11 = set_traingle(v7,v3,v5);
    ret.f12 = set_traingle(v5,v3,v1);
    ret.f21 = set_traingle(v3,v4,v1);
    ret.f22 = set_traingle(v4,v2,v1);
    ret.f31 = set_traingle(v2,v4,v8);
    ret.f32 = set_traingle(v8,v1,v2);
    ret.f41 = set_traingle(v6,v8,v7);
    ret.f42 = set_traingle(v6,v7,v5);
    ret.f51 = set_traingle(v5,v1,v6);
    ret.f52 = set_traingle(v1,v2,v6);
    ret.f61 = set_traingle(v8,v4,v7);
    ret.f62 = set_traingle(v7,v4,v3);

    return ret;
}

pyramid set_pyramid(float side_length, float height, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5 ){
    pyramid ret;
    float l = side_length/2, h = height/2;

    vertex v1 = set_vertex(set_point(  l,-h,   l), c1);
    vertex v2 = set_vertex(set_point(  l,-h,  -l), c2);
    vertex v3 = set_vertex(set_point( -l,-h,   l), c3);
    vertex v4 = set_vertex(set_point( -l,-h,  -l), c4);
    vertex v5 = set_vertex(set_point(0.0, h, 0.0), c5);


    ret.b1 = set_traingle(v2,v1,v3);
    ret.b2 = set_traingle(v2,v3,v4);
    ret.f1 = set_traingle(v3,v1,v5);
    ret.f2 = set_traingle(v1,v2,v5);
    ret.f3 = set_traingle(v2,v4,v5);
    ret.f4 = set_traingle(v4,v3,v5);

    return ret;
}
