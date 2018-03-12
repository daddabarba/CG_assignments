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
    double pi = acos(-1);

    double h = axis.dot(P-position);
    Vector projection_ax = h*axis + position;
    Vector projection_pl = (P - projection_ax).normalized();

    double theta = acos(((P - position).normalized()).dot(axis));
    double phi = acos(projection_pl.dot(clip));
	
    if(projection_pl.cross(clip).normalized() == axis)
        phi = 2*pi - phi;

    phi -= angle;

    if (phi<0)
        phi += 2*pi;

    else if (phi>2*pi)
        phi -= 2*pi;


    return Point(phi/(2*pi), (pi-theta)/(pi), 0.0);
}


Sphere::Sphere(Point const &pos, double radius, Vector ax, double ang)
:
    position(pos),
    r(radius),
    axis(ax.normalized()),
    angle((ang*acos(-1))/180.0)
{
    if (ax.y > std::numeric_limits<double>::epsilon())
        clip = Vector(1.0,-ax.x/ax.y,0.0);
    else if (ax.z > std::numeric_limits<double>::epsilon())
        clip = Vector(1.0,0.0,-ax.x/ax.z);
    else
        clip = Vector(-ax.y/ax.x, 1.0,0.0);

    clip.normalize();
}
