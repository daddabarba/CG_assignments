#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../object.h"

class Triangle: public Object
{
public:
    Triangle(Vector vertex1, Vector vertex2, Vector vertex3);

    virtual Hit intersect(Ray const &ray);

    Vector P1;
    Vector P2;
    Vector P3;

    Vector N;
    double O;


    Vector S12;
    double A213;
    Vector S31;
    double A132;

};

#endif
