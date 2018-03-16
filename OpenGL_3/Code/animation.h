#ifndef ANIMATION_H
#define ANIMATION_H

#include <QVector>

#include "transform.h"

typedef struct instruction{
 Transform gradient;
 unsigned int duration;
}instruction;

instruction make_instruction();

class animation
{
public:
    animation();

    void apply(Transform *transformation);

    void go(float x, float y, float z, unsigned int duration, bool contemp=false);
    void rotate(float x, float y, float z, unsigned int duration, bool contemp=false);

    QVector <instruction> sequence;
    unsigned int current;
    unsigned int time;
};

#endif // ANIMATION_H
