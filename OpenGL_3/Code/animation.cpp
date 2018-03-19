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

//compute 1 step of animation
void animation::apply(Transform *transformation){
    //don't do anything if animation is not specified
    if(sequence.length()==0)
        return;

    //check when step is finished, and move to next command
    if(time == (sequence.data())[current].duration){
        current = (current+1)%(sequence.length());
        time = 0;
    }

    //apply gradient to transformation matrix
    (*transformation) = (*transformation) + (sequence.data())[current].gradient;
    time += 1;
}

//change translation
void animation::go(float x, float y, float z, unsigned int duration, bool contemp){
    //contemp specifies that this command must be executed at the same time as the previous one
    if(contemp){
        //get last command
        instruction *command = sequence.data() + sequence.length() -1;
        //add translation gradient to last command
        (command->gradient).setPosition(x,y,z);

        return;
    }

    //make new command
    instruction command = make_instruction();

    //add translation gradient to new command
    (command.gradient).setPosition(x,y,z);
    //set duration
    command.duration = duration;

    sequence.append(command);
}

//change rotation
void animation::rotate(float x, float y, float z, unsigned int duration, bool contemp){
    //contemp specifies that this command must be executed at the same time as the previous one
    if(contemp){
        //get last command
        instruction *command = sequence.data() + sequence.length() -1;

        //add rotation gradient to last command
        (command->gradient).setRotation(x,y,z);

        return;
    }

    //make new command
    instruction command = make_instruction();

    //add rotation gradient to new command
    (command.gradient).setRotation(x,y,z);
    //set duration
    command.duration = duration;

    sequence.append(command);
}


