#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"
#include <cmath>

class Sphere: public Object
{
    public:
        Sphere(Point const &pos, double radius, Vector ax = Vector(0.0,0.0,1.0), double ang=0.0);

        virtual Hit intersect(Ray const &ray);
        Point map_tex (Point P) override;

        Point const position;
        double const r;

        Vector axis;
        double angle;
};

#endif
