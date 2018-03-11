#ifndef CONE_H
#define CONE_H

#include "../object.h"

class Cone: public Object
{
public:
    Cone(Vector origin, Vector direction, double height, double radius, double ang=0.0, bool fit_tex=false);

    virtual Hit intersect(Ray const &ray);
    Point map_tex(Point P) override ;

    Vector O;
    Vector D;
    double r;
    double h;

    Vector clip,
    double angle,

    bool triangular_tex;

};

#endif
