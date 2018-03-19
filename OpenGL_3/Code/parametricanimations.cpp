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

//change position of origin
void ellipse::move_center(point p){
    O = p;
}

//apply animation step to given transformation
void ellipse::apply(Transform *transform){
    //compute point position
    point position = current_pos();

    //change object position to computed one
    transform->setPosition(position.x,position.y,position.z);
    //rotate object on its own axis
    (transform->rotY) += rotation_speed;

    //increase time count
    step += 1;
}

//get current position (at time "step")
point ellipse::current_pos(){
    return at(step);
}

//get position at time "s"
point ellipse::at(unsigned int s){
    //get continuous time
    double t = (double)s * speed;

    //parametric bivariate definition of ellipse
    //apply bivariate values to make linear combination of axis
    point u = scale_point(ax1, width1*cos(t));
    point v = scale_point(ax2, width2*sin(t));
    //translate (add origin)
    point position = add_point(add_point(u,v), O);

    return position;
}
