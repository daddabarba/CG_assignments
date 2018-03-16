#include "parametricanimations.h"
#include <cmath>

ellipse::ellipse(point origin, point axis1, point axis2, double par1, double par2, double speed_in, double rot_speed)
    :
      O(origin),
      ax1(axis1),
      ax2(axis2),
      width1(par1),
      width2(par2),
      speed(speed_in),
      step(1),
      rotation_speed(rot_speed)
{
    ax1 = scale_point(ax1,(1.0f/point_distance(ax1)));
    ax2 = scale_point(ax2,(1.0f/point_distance(ax2)));
}

void ellipse::move_center(point p){
    O = p;
}

void ellipse::apply(Transform *transform){
    point position = current_pos();

    transform->setPosition(position.x,position.y,position.z);
    (transform->rotY) += rotation_speed;

    step += 1;
}

point ellipse::current_pos(){
    return at(step);
}

point ellipse::at(unsigned int s){
    double t = (double)s * speed;

    point u = scale_point(ax1, width1*cos(t));
    point v = scale_point(ax2, width2*sin(t));
    point position = add_point(add_point(u,v), O);

    return position;
}
