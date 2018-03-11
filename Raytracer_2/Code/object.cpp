#include "object.h"

bool Object::has_tex(){
    return material.has_tex;
}

Point Object::map_tex(Point P) {
    material.has_tex = false;
    return Point(-1.0,-1.0,0.0);
}

const Color &Object::get_tex_col(Point P){
    return material.get_tex_col(P);
}