#ifndef CYLINDER_H
#define CYLINDER_H

#include "../object.h"

class Cylinder: public Object
{
public:
    Cylinder(Vector origin, Vector direction, double height, double radius, double ang = 0.0);

    virtual Hit intersect(Ray const &ray);
    Point map_tex(Point P) override ;

    Vector O; //origin
    Vector D; //axis
    double r; //radius length
    double h; //height

    Vector clip; //landmark vector for u coordinates
    double angle; //texture rotation around axis
};

#endif
