#include "triangle.h"

Hit Triangle::intersect(Ray const &ray)
{
    if((ray.D.normalized()).dot(N) == 0)
        return Hit::NO_HIT();

    double t = (-O - (ray.O).dot(N))/((ray.D).dot(N));

    if (t<0.0)
        return Hit::NO_HIT();

    Vector P = ray.at(t);

    double angularDeviation1 = S12.dot((P-P1).normalized());
    Vector direction1 = S12.cross((P-P1)).normalized();
    bool isSameDirection1 = (direction1.x*N.x)>=0 && (direction1.y*N.y)>=0 && (direction1.z*N.z)>=0;
    bool isInAngle1 = angularDeviation1>=A213 && isSameDirection1;

    double angularDeviation2 = S31.dot((P-P3).normalized());
    Vector direction2 = S31.cross((P-P3)).normalized();
    bool isSameDirection2 = (direction2.x*N.x)>=0 && (direction2.y*N.y)>=0 && (direction2.z*N.z)>=0;
    bool isInAngle2 = angularDeviation2>=A132 && isSameDirection2;

    if(!isInAngle1 || !isInAngle2) {
        return Hit::NO_HIT();
    }

    return Hit(t, N);
}

Triangle::Triangle(Vector vertex1, Vector vertex2, Vector vertex3)
        :
        P1(vertex1),
        P2(vertex2),
        P3(vertex3),

        N(((P2-P1).cross(P3-P1)).normalized()),
        O(-(N.dot(P1))),

        S12((P2-P1).normalized()),
        A213(S12.dot((P3-P1).normalized())),

        S31((P1-P3).normalized()),
        A132(S31.dot((P2-P3).normalized()))
{}
