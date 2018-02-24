#include "cylinder.h"

#include <cmath>

using namespace std;

Hit Cylinder::intersect(Ray const &ray)
{
    double k = -(D.dot(O-ray.O))/D.length_2();
    double j = (D.dot(ray.D))/D.length_2();


    double top_t = (h-k)/j;
    double bottom_t = (-k)/j;

    double extreme_t = min(top_t, bottom_t);
    Vector extreme_N = (top_t<bottom_t)?(D+0.0):(-D);
    Vector center = (top_t<bottom_t)?(O+D*h):(O);
    bool at_extreme = (ray.at(extreme_t)- center).length() <= r;

    Hit failure = (!at_extreme)?(Hit::NO_HIT()):(Hit(extreme_t, extreme_N));


    Vector dir = ray.D - D*j;
    Vector ori = ray.O - O - D*k;

    double a = dir.length_2();
    double b = 2*dir.dot(ori);
    double c = ori.length_2() - r*r;

    double term_first  = -b;
    double term_second = b*b -4*a*c;

    if(term_second<0)
        return failure;

    double t1 = (term_first+sqrt(term_second))/(2*a);
    double t2 = (term_first-sqrt(term_second))/(2*a);

    double low = min(t1,t2);
    double high = max(t1,t2);

    double t = low;
    if(t<0){
        t = high;
        if(t<0){
            return failure;
        }
    }

    Vector P = ray.at(t);
    double height = t*j + k;

    if(height<0 || height>h)
        return failure;

    Vector N = (P - (O+height*D)).normalized();
    return (extreme_t < t && at_extreme)?(failure):(Hit(t,N));
}

Cylinder::Cylinder(Vector origin, Vector direction, double height, double radius)
        :
        O(origin),
        D(direction.normalized()),
        r(radius),
        h(height)
{}
