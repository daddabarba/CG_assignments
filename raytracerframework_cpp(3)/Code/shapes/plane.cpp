#include "plane.h"

Hit Plane::intersect(Ray const &ray)
{
    if((ray.D.normalized()).dot(N) == 0)
        return Hit::NO_HIT();

    double t = (-O - (ray.O).dot(N))/((ray.D).dot(N));

    if (t<0.0)
        return Hit::NO_HIT();

    return Hit(t, N);
}

Plane::Plane(Vector normal, double origin)
:
    N(normal.normalized()),
    O(origin)
{}
