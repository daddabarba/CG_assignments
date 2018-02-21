#include "sphere.h"

#include <cmath>

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    *
    * Insert calculation of ray/sphere intersection here.
    *
    * You have the sphere's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    // place holder for actual intersection calculation

    /*Vector OC = (position - ray.O).normalized();
    if (OC.dot(ray.D) < 0.999) {
        return Hit::NO_HIT();
    }
    double t = 1000;*/
    
    Triple dist = ray.O - position;
    
    double a = (ray.D).dot(ray.D);
    double b = 2*(ray.D).dot(dist);
    double c = dist.dot(dist) - r*r;
    
    double term_first  = -b;
    double term_second = b*b -4*a*c;
    
    if(term_second<0)
		return Hit::NO_HIT();
    
    double t1 = (term_first+sqrt(term_second))/2;
    double t2 = (term_first-sqrt(term_second))/2;
    
    double low = min(t1,t2);
    double high = max(t1,t2);
    
    double t = low;
    if(t<0){
			t = high;
			if(t<0){
					return Hit::NO_HIT();
			}
	}

    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/

    Vector N = (ray.at(t) - position).normalized();

    return Hit(t,N);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}
