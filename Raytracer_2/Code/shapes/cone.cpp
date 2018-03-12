#include "cone.h"

#include <cmath>

using namespace std;

Hit Cone::intersect(Ray const &ray)
{
    //the axis of the cone is also a parametrized line, with equation
    //O + height*D, with 0<=height<=h. The projection of a point P on the
    //given ray, onto this axis, is also in function of t. In particular we
    //have height = k + j*t (with k and j below defined)

    //The cone is much like the cylinder, only that r is also in function of height thus t

    double k = -(D.dot(O-ray.O))/D.length_2();
    double j = (D.dot(ray.D))/D.length_2();

    //find t where projection is the center of the bottom circle
    double bottom_t = (-k)/j;

    bool at_extreme = true; //if there is an intersection with the base
    Hit failure = Hit::NO_HIT();   //if no intersection with side, return intersection with base (if there)

    //discard negative intersection
    if(bottom_t<0){
        at_extreme = false;
    }

    if(at_extreme) {
        //normal is inverse of direction
        Vector extreme_N = -D;
        //get if base intersection
        at_extreme = (ray.at(bottom_t) - O).length() <= r;

        //what to return in case there is no side intersection (there might be one with the base)
        failure = (!at_extreme) ? (Hit::NO_HIT()) : (Hit(bottom_t, extreme_N));
    }


    //components of second degree equation for distance between point on ray P and cylinder axis
    Vector dir = ray.D - D*j;
    Vector ori = ray.O - O - D*k;

    //a,b, and c components (same as cylinder, with addition of radius definition in time)
    double a = dir.length_2() - j*j*(r/h)*(r/h);
    double b = 2*dir.dot(ori) -2*j*k*(r/h)*(r/h) + 2*((r*r)/h)*j;
    double c = ori.length_2() - r*r - k*k*(r/h)*(r/h) +2*((r*r)/h)*k;

    //nominator addends of the abc formula
    double term_first  = -b;
    double term_second = b*b -4*a*c;

    //check if intersection
    if(term_second<0)
        return failure;

    //get two intersection values
    double t1 = (term_first+sqrt(term_second))/(2*a);
    double t2 = (term_first-sqrt(term_second))/(2*a);

    //discard lower and negative time
    double t = min(t1,t2);
    if(t<0){
        t = max(t1,t2);
        if(t<0){
            return failure;
        }
    }

    //get intersection point and projection height
    Vector P = ray.at(t);
    double height = t*j + k;

    //check if projection in height limit of cylinder
    if(height<0 || height>h)
        return failure;

    //normal is vector from projection (on axis) to P
    Vector N = (P - (O+height*D)).normalized();
    return (bottom_t < t && at_extreme)?(failure):(Hit(t,N));
}

Point Cone::map_tex(Point P) {
    double pi = acos(-1);
    double height = (P-O).dot(D);

    Vector projection = height*D + O;
    Vector ang_pos = (P-projection).normalized();

    double alpha = acos(ang_pos.dot(clip));

    if(ang_pos.cross(clip).normalized() == D)
        alpha = 2*pi - alpha;

    alpha -= angle;

    if(alpha<0)
        alpha += 2*pi;
    if(alpha>2*pi)
        alpha -= 2*pi;

    double u = alpha/(2*pi);
    if(triangular_tex)
        u = (1.0-height)*u + height/2.0;

    return Point(u,height/h,0.0);
}

Cone::Cone(Vector origin, Vector direction, double height, double radius, double ang, bool fit_tex)
        :
        O(origin), //center of base (circle)
        D(direction.normalized()), //normalized direction (axis of cone)
        r(radius), //radius of cone
        h(height), //height of cone

        clip(Vector(1.0,-direction.x/direction.y,0.0).normalized()),
        angle(ang),

        triangular_tex(fit_tex)
{}
