#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <limits>

using namespace std;

Color Scene::trace(Ray const &ray)
{
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx)
    {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t)
        {
            min_hit = hit;
            obj = objects[idx];
        }
    }

    // No hit? Return background color.
    if (!obj) return Color(0.0, 0.0, 0.0);

    Material material = obj->material;          //the hit objects material
    Point hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector

    //initializing ambient, diffuse and specular illumination to black
    Color I_A(0.0,0.0,0.0);
    Color I_D(0.0,0.0,0.0);
    Color I_S(0.0,0.0,0.0);

    //ambient illumination is constant
    I_A = material.color*material.ka;

    //for every light source
    for (unsigned idx = 0; idx != lights.size(); ++idx) {
		//compute vector from intersection point to light
        Vector L = (lights[idx]->position - hit).normalized();
        //compute reflected vector
		Vector R = 2*(N.dot(L))*N - L;

        //add diffusion illumination for this light
		I_D += material.color*(lights[idx]->color)*(material.kd)*(max(0.0,L.dot(N)));
        //add specular illumination for this light
		I_S += (lights[idx]->color)*(material.ks)*pow(max(0.0,V.dot(R)),material.n);
	}

    //compute final color
    Color color = I_A + I_D + I_S;

    return color;
}

void Scene::render(Image &img)
{
    unsigned w = img.width();
    unsigned h = img.height();
    for (unsigned y = 0; y < h; ++y)
    {
        for (unsigned x = 0; x < w; ++x)
        {
            Point pixel(x + 0.5, h - 1 - y + 0.5, 0);
            Ray ray(eye, (pixel - eye).normalized());
            Color col = trace(ray);
            col.clamp();
            img(x, y) = col;
        }
    }

	/*// Anti-Aliasing (16 samples)
	for (float y = 0; y < h; y += 0.25f)
	{
		for (float x = 0; x < w; x += 0.25f)
		{
			Point pixel(x, h - 1 - y, 0);
			Ray ray(eye, (pixel - eye).normalized());
			Color col = trace(ray);
			col.clamp();
			img((int)x, (int)y) += col / 16;
		}
	}*/
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
