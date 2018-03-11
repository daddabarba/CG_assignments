#include "material.h"

void Material::set_tex(std::string const &path) {
    texture = Image(path);
    has_tex = true;
}

const Color &Material::get_tex_col(Point P) {
    return texture.colorAt(P.x,P.y);
}