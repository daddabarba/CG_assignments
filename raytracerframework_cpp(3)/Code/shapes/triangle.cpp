#include "triangle.h"

Hit Triangle::intersect(Ray const &ray)
{

    //Triangle's plane intersection

    //check if ray is parallel to plane on which triangle lays
    if((ray.D.normalized()).dot(N) == 0)
        return Hit::NO_HIT();

    //get intersection point between ray and triangle's plane
    double t = (-O - (ray.O).dot(N))/((ray.D).dot(N));

    if (t<0.0)
        return Hit::NO_HIT();


    //Checking that intersection is also in triangle

    //get intersection coordinates (with plane)
    Vector P = ray.at(t);

    //triangle is intersection area of 2 angles

    //check that P is in P2-P1-P3 angle

    //cosine of angle between P1-P2 side and P1-P vector
    double angularDeviation1 = S12.dot((P-P1).normalized());
    //excluding clockwise angles (cosine symmetric)
    Vector direction1 = S12.cross((P-P1)).normalized();
    bool isSameDirection1 = (direction1.x*N.x)>=0 && (direction1.y*N.y)>=0 && (direction1.z*N.z)>=0;
    //checking that is inside angle (same direction and smaller angle than that of the triangle)
    bool isInAngle1 = angularDeviation1>=A213 && isSameDirection1;


    //check that P is in P1-P3-P2 angle

    //cosine of angle between P3-P1 side and P3-P vector
    double angularDeviation2 = S31.dot((P-P3).normalized());
    //excluding clockwise angles (cosine symmetric)
    Vector direction2 = S31.cross((P-P3)).normalized();
    bool isSameDirection2 = (direction2.x*N.x)>=0 && (direction2.y*N.y)>=0 && (direction2.z*N.z)>=0;
    //checking that is inside angle (same direction and smaller angle than that of the triangle)
    bool isInAngle2 = angularDeviation2>=A132 && isSameDirection2;

    //if P is not in one of the two angles, then it is outside of the triangle
    if(!isInAngle1 || !isInAngle2) {
        return Hit::NO_HIT();
    }

    return Hit(t, N);
}

Triangle::Triangle(Vector vertex1, Vector vertex2, Vector vertex3)
        :
        P1(vertex1), //vertex 1 of triangle
        P2(vertex2), //vertex 2 of triangle
        P3(vertex3), //vertex 3 of triangle

        //triangle's normal (constant). Also triangle's plane coefficients
        N(((P2-P1).cross(P3-P1)).normalized()),
        //triangle's plane free term
        O(-(N.dot(P1))),

        //normalized vector for P1-P2 side
        S12((P2-P1).normalized()),
        //cosine of angle P2-P1-P3
        A213(S12.dot((P3-P1).normalized())),

        //normalized vector for P3-P1 side
        S31((P1-P3).normalized()),
        //cosine of angle P1-P3-P2
        A132(S31.dot((P2-P3).normalized()))
{}
