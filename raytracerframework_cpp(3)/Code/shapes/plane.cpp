#include "plane.h"

Hit Plane::intersect(Ray const &ray)
{
	// check if plane and ray are parallel to avoid dividing by 0
    if((ray.D.normalized()).dot(N) == 0)
        return Hit::NO_HIT();

	// if they're not parallel, there is always a point t at which the ray meets the plane
    double t = (-O - (ray.O).dot(N))/((ray.D).dot(N));

	// check if intersection point is behind the observer
    if (t<0.0)
        return Hit::NO_HIT();
	
    return Hit(t, N);
}

Plane::Plane(Vector normal, double origin)
:
    N(normal.normalized()),
    O(origin)
{}
