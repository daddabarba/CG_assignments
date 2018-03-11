#include "sphere.h"
#include "solvers.h"

#include <cmath>

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
    // Sphere formula: ||x - position||^2 = r^2
    // Line formula:   x = ray.O + t * ray.D

    Vector L = ray.O - position;
    double a = ray.D.dot(ray.D);
    double b = 2 * ray.D.dot(L);
    double c = L.dot(L) - r * r;

    double t0;
    double t1;
    if (not Solvers::quadratic(a, b, c, t0, t1))
        return Hit::NO_HIT();

    // t0 is closest hit
    if (t0 < 0)  // check if it is not behind the camera
    {
        t0 = t1;    // try t1
        if (t0 < 0) // both behind the camera
            return Hit::NO_HIT();
    }

    // calculate normal
    Point hit = ray.at(t0);
    Vector N = (hit - position).normalized();

    // determine orientation of the normal
    if (N.dot(ray.D) > 0)
        N = -N;

    return Hit(t0, N);
}

Point Sphere::map_tex(Point P){
    double pi = atan(1)*4;

    double theta = acos(((P-position)/r).dot(axis));
    double phi = atan2(P.y-position.y,P.x-position.x) - angle;

    return Point(phi/(2*pi), (pi-theta)/pi, 0.0);
}

Sphere::Sphere(Point const &pos, double radius, Vector ax, double ang)
:
    position(pos),
    r(radius),
    axis(ax.normalized()),
    angle(ang)
{}
