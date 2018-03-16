#ifndef PARAMETRICANIMATIONS
#define PARAMETRICANIMATIONS

#include "geoms.h"
#include "transform.h"

class ellipse{
public:
    ellipse(point origin= set_point(0.0,0.0,0.0), point axis1= set_point(0.0,0.0,0.0), point axis2= set_point(0.0,0.0,0.0), double par1=1.0f, double par2=1.0f, double speed_in = 0.1f, double rot_speed=0.01f);

    void move_center(point p);
    void apply(Transform *transform);

    point current_pos();
    virtual point at(unsigned int s);

    point O;
    point ax1,ax2;
    double width1, width2;

    double speed;
    unsigned int step;

    double rotation_speed;
};

#endif // PARAMETRICANIMATIONS

