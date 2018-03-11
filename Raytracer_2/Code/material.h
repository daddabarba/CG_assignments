#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "triple.h"
#include "image.h"
#include "json/json.h"

class Material
{
    public:
        Color color;        // base color
        double ka;          // ambient intensity
        double kd;          // diffuse intensity
        double ks;          // specular intensity
        double n;           // exponent for specular highlight size

        Material() = default;

        Image texture;
        bool has_tex;

        void set_tex(std::string const &path);
        const Color &get_tex_col(Point P);

        Material(double ka, double kd, double ks, double n, Color const &color=Color(0.0,0.0,0.0))
        :
            color(color),
            ka(ka),
            kd(kd),
            ks(ks),
            n(n),
            texture(),
            has_tex(false)
        {}
};

#endif
