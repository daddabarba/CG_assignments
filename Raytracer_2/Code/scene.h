#ifndef SCENE_H_
#define SCENE_H_

#include "light.h"
#include "object.h"
#include "triple.h"

#include <vector>

// Forward declerations
class Ray;
class Image;

class Scene
{
    std::vector<ObjectPtr> objects;
    std::vector<LightPtr> lights;   // no ptr needed, but kept for consistency
    Point eye;

    public:

        // trace a ray into the scene and return the color
        Color trace(Ray const &ray, int depth=0);

        void light(Light l, Point P, Vector N, Vector V, Material m, Color *I_D, Color *I_S);
        Hit shoot_ray(Ray const &ray, ObjectPtr *obj=nullptr);

        // render the scene to the given image
        void render(Image &img);


        void addObject(ObjectPtr obj);
        void addLight(Light const &light);
        void setEye(Triple const &position);

        unsigned getNumObject();
        unsigned getNumLights();
        
        bool shadows;
        unsigned ss_factor;

        int waves;
};

#endif
