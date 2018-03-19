#ifndef PARAMETRICANIMATIONS
#define PARAMETRICANIMATIONS

#include "geoms.h"
#include "transform.h"

class ellipse{
public:
    ellipse(point origin= set_point(0.0,0.0,0.0), point axis1= set_point(0.0,0.0,0.0), point axis2= set_point(0.0,0.0,0.0), double par1=1.0f, double par2=1.0f, double speed_in = 0.1f, double rot_speed=0.01f);

    void move_center(point p); //change position of origin
    void apply(Transform *transform); //apply animation step to given transformation

    point current_pos(); //get current position (at time "step")
    virtual point at(unsigned int s); //get position at time "s"

    point O; //origin (of axis vectors)
    point ax1,ax2; //axis vectors (define ellipse plane with span)
    double width1, width2; //length of ellipse's axis

    double speed; //speed
    unsigned int step; //discrete time-step

    double rotation_speed; //speed of rotation on object's own axis
};

#endif // PARAMETRICANIMATIONS

