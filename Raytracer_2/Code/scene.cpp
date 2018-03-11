#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <limits>

using namespace std;

Color Scene::trace(Ray const &ray, int depth)
{
    Color color;

    // Find hit object and distance
    ObjectPtr obj = nullptr;
    Hit min_hit = shoot_ray(ray, &obj);

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material material = obj->material;          //the hit objects material
    Point hit = ray.at(min_hit.t - 0.0000000001);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector

    Point uv_coord = obj->map_tex(hit);

    if(obj->has_tex()) {
        color = obj->get_tex_col(uv_coord);
    } else {
		
        //initializing ambient, diffuse and specular illumination to black
        Color I_A(0.0, 0.0, 0.0);
        Color I_D(0.0, 0.0, 0.0);
        Color I_S(0.0, 0.0, 0.0);

        //ambient illumination is constant
        I_A = material.color * material.ka;
		
        //for every light source
        for (unsigned idx = 0; idx != lights.size(); ++idx) {
            if (shadows) {
                Ray shadowCheck(hit, lights[idx]->position - hit);
                bool intersection = false;
                for (unsigned io = 0; io != objects.size(); ++io) {
                    if (objects[io]->intersect(shadowCheck).t < (lights[idx]->position - hit).length()) {
                        intersection = true;
                        break;
                    }
                }
                if (intersection) continue;
            }

            light(*lights[idx], hit, N, V, material, &I_D, &I_S);
        }
		
        //REFLECTING
        if (depth < waves) {
            //Reflecting direction
            Vector R = 2 * (N.dot(-ray.D)) * N + ray.D;
            //Ray from hit point towards reflected direction
            Ray r_ray(hit, R);

            //Object impacted by reflected ray
            ObjectPtr r_obj = nullptr;
            //Hit of reflected ray
            Hit r_min_hit = shoot_ray(r_ray, &r_obj);

            //If the reflected ray hits something
            if (r_obj != nullptr) {
                //get incident point (reflected light source origin)
                Point r_hit = r_ray.at(r_min_hit.t);

                //Make reflected light source (recursively compute color)
                Light r_light(r_hit, trace(r_ray, depth + 1));
                //Apply light source
                Color ID_ref;
                light(r_light, hit, N, V, material, &ID_ref, &I_S);
            }
        }

        //compute final color
        color = I_A + I_D + I_S;
    }

    return color;
}

//AUXILIARY FUNCTIONS

//Computes diffuse and specular components at hit, given a light
void Scene::light(Light l, Point P, Vector N, Vector V, Material m, Color *I_D, Color *I_S){
    //compute vector from intersection point to light
    Vector L = (l.position - P).normalized();
    //compute reflected vector
    Vector R = 2*(N.dot(L))*N - L;

    //add diffusion illumination for this light
    *I_D += m.color*(l.color)*(m.kd)*(max(0.0,L.dot(N)));
    //add specular illumination for this light
    *I_S += (l.color)*(m.ks)*pow(max(0.0,V.dot(R)),m.n);
}

//Computes hit (and object) of given ray
Hit Scene::shoot_ray(Ray const &ray, ObjectPtr *obj){
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;

            if(obj!= nullptr)
                *obj = objects[idx];
        }
    }

    return min_hit;
}

//RENDERING

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();
    for (float y = 0.5f / ss_factor; y < h; y += 1.0f / ss_factor)
    {
        for (float x = 0.5f / ss_factor; x < w; x += 1.0f / ss_factor)
        {
            Point pixel(x + 0.5, h - 1 - y + 0.5, 0);
            Ray ray(eye, (pixel - eye).normalized());
            Color col = trace(ray);
            col.clamp();
            img((int)x, (int)y) += col / (ss_factor * ss_factor);
        }
    }
}



// --- Misc functions ----------------------------------------------------------

void Scene::addObject(ObjectPtr obj)
{
    objects.push_back(obj);
}

void Scene::addLight(Light const &light)
{
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position)
{
    eye = position;
}

unsigned Scene::getNumObject()
{
    return objects.size();
}

unsigned Scene::getNumLights()
{
    return lights.size();
}
