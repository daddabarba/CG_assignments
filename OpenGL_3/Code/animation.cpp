#include "animation.h"


instruction make_instruction(){
    instruction ret;

    ret.gradient = Transform();
    ret.duration = 0;

    (ret.gradient).setScale(0.0f);

    return ret;
}

animation::animation()
    :
      sequence(),
      current(0),
      time(0)
{}

void animation::apply(Transform *transformation){

    if(sequence.length()==0)
        return;

    if(time == (sequence.data())[current].duration){
        current = (current+1)%(sequence.length());
        time = 0;
    }

    (*transformation) = (*transformation) + (sequence.data())[current].gradient;
    time += 1;
}

void animation::go(float x, float y, float z, unsigned int duration, bool contemp){
    if(contemp){
        instruction *command = sequence.data() + sequence.length() -1;

        (command->gradient).setPosition(x,y,z);

        return;
    }

    instruction command = make_instruction();

    (command.gradient).setPosition(x,y,z);
    command.duration = duration;

    sequence.append(command);
}

void animation::rotate(float x, float y, float z, unsigned int duration, bool contemp){
    if(contemp){
        instruction *command = sequence.data() + sequence.length() -1;

        (command->gradient).setRotation(x,y,z);

        return;
    }

    instruction command = make_instruction();

    (command.gradient).setRotation(x,y,z);
    command.duration = duration;

    sequence.append(command);
}


