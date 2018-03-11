#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"
#include <cmath>

class Sphere: public Object
{
    public:
        Sphere(Point const &pos, double radius);

        virtual Hit intersect(Ray const &ray);
        Point map_tex (Point P) override;

        Point const position;
        double const r;
};

#endif
