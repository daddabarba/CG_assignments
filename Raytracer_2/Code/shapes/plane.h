#ifndef PLANE_H
#define PLANE_H

#include "../object.h"

class Plane: public Object
{
public:
    Plane(Vector normal, double origin);

    virtual Hit intersect(Ray const &ray);

    Vector N;
    double O;
};

#endif
