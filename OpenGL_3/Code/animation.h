#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector>

#include "transform.h"

//single instruction (gradient over transformation matrix)
typedef struct instruction{
 Transform gradient; //gradient of transformation matrix (on translation and rotation)
 unsigned int duration;//number of times the gradient must be applied
}instruction;

instruction make_instruction();

class animation
{
public:
    animation();

    void apply(Transform *transformation); //compute 1 step of animation

    void go(float x, float y, float z, unsigned int duration, bool contemp=false); //change translation
    void rotate(float x, float y, float z, unsigned int duration, bool contemp=false); //change rotation

    QVector <instruction> sequence;
    unsigned int current; //current command in animation list (index)
    unsigned int time; //discrete time
};

#endif // ANIMATION_H
