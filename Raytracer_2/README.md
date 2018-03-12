# Raytracer C++ framework for Introduction to Computer Graphics

#############
#DESCRIPTION#
#############

To run the code please refer to the assignment instructions (## Compiling the code
and ## Running the Raytracer). When running the raytracer there are 5 different scenes
which can be rendered: scene01.json,scene02.json (given for the assignment),
scene03.json (showing most of the shapes implemented),scene04.json (showing shapes and
meshes), and scene05.json (mesh of a tea-pot).

####################
#CURRENT ASSIGNMENT#
####################

For the first part of this assignment, the method "trace" of the class "scene" has been
modified.

- for SHADOWS we added a check (after finding an intersection point of the ray with an object)
where we shoot the a ray from the intersection to the light, and if it intersects an object
before the light, then it is shaded

- we already LOOPED OVER LIGHT SOURCES

- for REFLECTIONS, the method was modified with an extra argument depth (number of reflections),
which is by default 0. We added an argument "waves" to set the depth limit.
Then "trace" is recursively called with a reflected ray, and the resulting intersection
point and color compose a new light source.
To facilitate code reading, we wrapped in two new methods: the procedure of shooting a ray
(getting its first intersection), and adding to the Diffuse and Specular component the effects
of a single light source.

For ANTIALIASING ----

The method "readScene", in the "raytracer" class was changed so that it could read the maximum
reflection depth, whether or not we wanted shadows, and the sampling size for anti-aliasing
from a json file.


Regarding TEXTURING we first modified the "object" and "material" classes. The latter to
contain and load a texture file, the former to easily access and change these new material features.
The methods "parseObject" and "parseMaterial" have been changed so that the new texture arguments
of the objects (see below) and the texture specifications can be red.

Regarding the objects the "sphere" class (and also the "cylinder" and "cone" classes
accordingly) have been modified. First we added some arguments keeping track of the rotation,
that is an axis, and an angle of rotation around the axis. Then we added an override of
the method "map_tex" (added to the "object" class), which, given a point P, will return
its respective (u,v) coordinates.
In the SPHERE this has been done by using the normalized angle between the tangent vector
(from center to surface point) and the rotation axis as v coordinate. For the u coordinate
we project the tangent vector on the plane defined by the rotation axis, on which we have
pre computed (in the constructor) a landmark vector (such that it is always on this plane).
The normalize angle between the landmark and the projection is the u coordinate.
For CONE and CYLINDER the process is very similar (we already have an axis for them, so
we only added texture rotation around it), only that v is the normalized height (on the axis).

Also do notice that in the class "triple" we added the operator == as it is needed in the sphere
"map_tex" method

#####################
#PREVIOUS ASSIGNMENT#
#####################

In this assignment 5 shapes have been added (in Code/shapes). These have been implemented
as c++ classes, therefore having both an header and a cpp file.
The added classes are the following:
·cone [center of base, direction of axis (to rotate), radius, and height]
·cylinder [center of base, direction of axis (to rotate), radius, and height]
·plane [normal of plane/abc coefficients, free term/translation]
·triangle [3 vertices]
·mesh [array of triangles]

In addition the shape sphere was modified (more precisely the intersection method,
computing intersection point and normal at intersection).

In the file scene.cpp Phong illumination was added, while in the raytracer.cpp the procedure
to read shapes where included (for each of the aforementioned shapes).



#########################
#ASSIGNMENT INSTRUCTIONS#
#########################

This is a C++ framework for a raytracer. It is created for the Computer
Science course "Introduction to Computer Graphics" taught at the
University of Groningen.

This framework is inspired by and uses (some) code of the raytracer framework of
Bert Freudenberg which unfortunately is no longer available.

## Compiling the code

We provided a [CMakeLists.txt](CMakeLists.txt) file to be used with `cmake`.
This can be used in the following way (on the command line/shell):
```
# cd into the main directory of the framework
mkdir build   # create a new build directory
cd build      # cd into the directory
cmake ..      # creates a Makefile
# Comipiling the code can then be done with:
make
# or
make -j4      # replacing 4 with the number of cores of your pc
```
**Note!** After adding new `.cpp` files (when adding new shapes)
`cmake ..` needs to be called again or you might get linker errors.

## Running the Raytracer
After compilation you should have the `ray` executable.
This can be used like this:
```
./ray <path to .json file> [output .png file]
# when in the build directory:
./ray ../Scenes/scene01.json
```
Specifying an output is optional and by default an image will be created in
the same directory as the source scene file with the `.json` extension replaced
by `.png`.

## Description of the included files

### Scene files
* `Scenes/*.json`: Scene files are structured in JSON. If you have never
    worked with json, please see [here](https://en.wikipedia.org/wiki/JSON#Data_types,_syntax_and_example)
    or [here](https://www.json.org/).

    Take a look at the provided example scenes for the general structure.
    You are free (and encouraged) to define your own scene files later on.

### The raytracer source files (Code directory)

* `main.cpp`: Contains main(), starting point. Responsible for parsing
    command-line arguments.

* `raytracer.cpp/.h`: Raytracer class. Responsible for reading the scene
    description, starting the raytracer and writing the result to an image file.

* `scene.cpp/.h`: Scene class. Contains code for the actual raytracing.

* `image.cpp/.h`: Image class, includes code for reading from and writing to PNG
    files.

* `light.h`: Light class. Plain Old Data (POD) class. Colored light at a
    position in the scene.

* `ray.h`: Ray class. POD class. Ray from an origin point in a direction.

* `hit.h`: Hit class. POD class. Intersection between an `Ray` and an `Object`.

* `object.h`: virtual `Object` class. Represents an object in the scene.
    All your shapes should derive from this class. See

* `shapes (directory/folder)`: Folder containing all your shapes.

* `sphere.cpp/.h (inside shapes)`: Sphere class, which is a subclass of the
    `Object` class. Represents a sphere in the scene.

* `example.cpp/.h (inside shapes)`: Example shape class. Copy these two files
    and replace/rename **every** instance of `Example` `example.h` or `EXAMPLE`
    with your new shape name.

* `triple.cpp/.h`: Triple class. Represents a 3-dimensional vector which is
    used for colors, points and vectors.
    Includes a number of useful functions and operators, see the comments in
    `triple.h`.
    Classes of `Color`, `Vector`, `Point` are all aliases of `Triple`.

* `objloader.cpp/.h`: Is a similar class to Model used in the OpenGL
    exercises to load .obj model files. It produces a std::vector
    of Vertex structs. See `vertex.h` on how you can retrieve the
    coordinates and other data defined at vertices.

### Supporting source files (Code directory)

* `lode/*`: Code for reading from and writing to PNG files,
    used by the `Image` class.
    lodepng is created by Lode Vandevenne and can be found on
    [github](https://github.com/lvandeve/lodepng).
* `json/*`: Code for parsing JSON documents.
    Created by Niels Lohmann and available under the MIT license on
    [github](https://github.com/nlohmann/json).
    **Recommended:** Especially take a look at their README for more
    info on how to work with json files.
