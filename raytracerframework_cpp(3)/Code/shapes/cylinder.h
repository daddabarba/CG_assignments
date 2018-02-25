#ifndef CYLINDER_H
#define CYLINDER_H

#include "../object.h"

class Cylinder: public Object
{
public:
    Cylinder(Vector origin, Vector direction, double height, double radius);

    virtual Hit intersect(Ray const &ray);

    Vector O;
    Vector D;
    double r;
    double h;

};

#endif
