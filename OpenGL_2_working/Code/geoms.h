#ifndef GEOMS
#define GEOMS
/*
    BASIC TYPES
*/
typedef struct RGB_color{ //RGB color
    float r, g, b;
}RGB_color;

typedef struct point{ //3D point
    float x, y, z;
}BI_Point;

typedef struct vertex{ //Vertex (point with color)
     point position;
     RGB_color color;
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
point set_point(float x, float y, float z);

vertex set_vertex(point position, RGB_color color);

triangle set_traingle(vertex v1, vertex v2, vertex v3);

cube set_cube(float side_length, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5, RGB_color c6, RGB_color c7, RGB_color c8 );
pyramid set_pyramid(float side_length, float height, RGB_color c1, RGB_color c2, RGB_color c3, RGB_color c4, RGB_color c5 );

#endif // GEOMS
