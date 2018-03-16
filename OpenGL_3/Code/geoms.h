#ifndef GEOMS
#define GEOMS
/*
    BASIC TYPES
*/
typedef struct RGB_color{ //RGB color
    float r, g, b;
}RGB_color;

typedef struct phong_mat{ //material with ambient, diffuse, specular and specular exponent
    float a, d, s, e;
}phong_mat;

typedef struct point{ //3D point
    float x, y, z;
}BI_Point;

typedef struct coord {
    float x, y;
} coord;

typedef struct vertex{ //Vertex (point with color)
    point position;
    RGB_color color;
    coord texcoord;
}vertex;


/*
    POLYGONS
*/

typedef struct triangle{ //Trsuct defining a triangle, as 3 vertices
    vertex v1,v2,v3;
}triangle;


typedef struct cube{ //Struct defining a cube mesh, with argumens f<face><half face/triangle>
    triangle f11,f12,f21,f22,f31,f32,f41,f42,f51,f52,f61,f62;
}cube;

typedef struct pyramid{ //Struct defining a pyramid mesh, with arguments f<side face/triangle>, b<base half>
    triangle b1,b2,f1,f2,f3,f4;
}pyramid;


/*
    CREATOR FUNCTIONS (for structs)
*/

RGB_color set_color(float r, float g, float b);
phong_mat set_material(float a, float d, float s, float e);
coord set_coord(float x, float y);
point set_point(float x, float y, float z);

vertex set_vertex(point position, RGB_color color);
vertex set_vertex(point position, RGB_color color, coord texcoord);

triangle set_triangle(vertex v1, vertex v2, vertex v3);

cube set_cube(float side_length, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5, RGB_color c6, RGB_color c7, RGB_color c8 );
pyramid set_pyramid(float side_length, float height, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5 );

double point_distance(point p);

point scale_point(point p, double factor);
point add_point(point p, point t);

#endif // GEOMS

