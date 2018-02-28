#ifndef CONE_H
#define CONE_H

#include "../object.h"

class Cone: public Object
{
public:
    Cone(Vector origin, Vector direction, double height, double radius);

    virtual Hit intersect(Ray const &ray);

    Vector O;
    Vector D;
    double r;
    double h;

};

#endif
