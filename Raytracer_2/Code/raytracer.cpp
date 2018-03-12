#include "raytracer.h"

#include "image.h"
#include "light.h"
#include "material.h"
#include "triple.h"

// =============================================================================
// -- Include all your shapes here ---------------------------------------------
// =============================================================================

#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "shapes/triangle.h"
#include "shapes/cylinder.h"
#include "shapes/cone.h"
#include "shapes/mesh.h"

// =============================================================================
// -- End of shape includes ----------------------------------------------------
// =============================================================================

#include "json/json.h"

#include <exception>
#include <fstream>
#include <iostream>

using namespace std;        // no std:: required
using json = nlohmann::json;

bool Raytracer::parseObjectNode(json const &node)
{
    ObjectPtr obj = nullptr;

// =============================================================================
// -- Determine type and parse object parametrers ------------------------------
// =============================================================================

    if (node["type"] == "sphere")
    {
        Point pos(node["position"]);
        double radius = node["radius"];

        //read rotation and angle if given
        if(node.find("rotation")!=node.end() && node.find("angle")!=node.end())
            obj = ObjectPtr(new Sphere(pos, radius, Vector(node["rotation"]),node["angle"]));
        else
            obj = ObjectPtr(new Sphere(pos, radius));
    }
    else if (node["type"] == "plane")
    {
        Vector normal(node["normal"]);
        double origin = node["origin"];
        obj = ObjectPtr(new Plane(normal, origin));
    }
    else if (node["type"] == "triangle")
    {
        Point p1(node["point1"]);
        Point p2(node["point2"]);
        Point p3(node["point3"]);
        obj = ObjectPtr(new Triangle(p1,p2,p3));
    }
    else if (node["type"] == "cylinder")
    {
        Vector o(node["origin"]);
        Vector d(node["direction"]);
        double r = node["radius"];
        double h = node["height"];

        //read angle if given
        if(node.find("angle")!=node.end())
            obj = ObjectPtr(new Cylinder(o,d,h,r,node["angle"]));
        else
            obj = ObjectPtr(new Cylinder(o,d,h,r));
    }
    else if (node["type"] == "cone")
    {
        Vector o(node["origin"]);
        Vector d(node["direction"]);
        double r = node["radius"];
        double h = node["height"];

        bool fit_tex = false;

        //read angle if given
        if(node.find("angle")!=node.end()) {
            //read if texture is triangle if given)
            if (node.find("fit_tex") != node.end())
                fit_tex = node["fit_tex"];

            obj = ObjectPtr(new Cone(o, d, h, r, node["angle"], fit_tex));
        }else {
            obj = ObjectPtr(new Cone(o, d, h, r));
        }
    }
    else if (node["type"] == "mesh")
    {
		std::string const &model(node["model"]);
		Point pos(node["position"]);
		double scale(node["scale"]);
        obj = ObjectPtr(new Mesh(model, pos, scale));
    }
    else
    {
        cerr << "Unknown object type: " << node["type"] << ".\n";
    }

// =============================================================================
// -- End of object reading ----------------------------------------------------
// =============================================================================

    if (!obj)
        return false;

    // Parse material and add object to the scene
    obj->material = parseMaterialNode(node["material"]);
    scene.addObject(obj);
    return true;
}

Light Raytracer::parseLightNode(json const &node) const
{
    Point pos(node["position"]);
    Color col(node["color"]);
    return Light(pos, col);
}

Material Raytracer::parseMaterialNode(json const &node) const
{
    bool texturized = node.find("texture") != node.end();

    Color color;
    if(!texturized)
        color = Color(node["color"]);

    double ka = node["ka"];
    double kd = node["kd"];
    double ks = node["ks"];
    double n  = node["n"];

    Material material;
    if(!texturized)
        material = Material(ka, kd, ks, n, color);
    else
        material = Material(ka, kd, ks, n);

    if(texturized) {
         material.set_tex((string const &)node["texture"]);
    }

    return material;
}

bool Raytracer::readScene(string const &ifname)
try
{
    // Read and parse input json file
    ifstream infile(ifname);
    if (!infile) throw runtime_error("Could not open input file for reading.");
    json jsonscene;
    infile >> jsonscene;

// =============================================================================
// -- Read your scene data in this section -------------------------------------
// =============================================================================

    Point eye(jsonscene["Eye"]);
    scene.setEye(eye);

    // TODO: add your other configuration settings here
    
    if(jsonscene["Shadows"] != nullptr)
        scene.shadows = jsonscene["Shadows"];
    else
        scene.shadows = false;

    if(jsonscene["MaxRecursionDepth"] != nullptr)
        scene.waves = jsonscene["MaxRecursionDepth"];
    else
        scene.waves = 0;

    if (jsonscene["SuperSamplingFactor"] != nullptr) scene.ss_factor = jsonscene["SuperSamplingFactor"];
    else scene.ss_factor = 1;

    for (auto const &lightNode : jsonscene["Lights"])
        scene.addLight(parseLightNode(lightNode));

    unsigned objCount = 0;
    for (auto const &objectNode : jsonscene["Objects"])
        if (parseObjectNode(objectNode))
            ++objCount;

    cout << "Parsed " << objCount << " objects.\n";

// =============================================================================
// -- End of scene data reading ------------------------------------------------
// =============================================================================

    return true;
}

catch (exception const &ex)
{
    cerr << ex.what() << '\n';
    return false;
}

void Raytracer::renderToFile(string const &ofname)
{
    // TODO: the size may be a settings in your file
    Image img(400, 400);
    cout << "Tracing...\n";
    scene.render(img);
    cout << "Writing image to " << ofname << "...\n";
    img.write_png(ofname);
    cout << "Done.\n";
}
