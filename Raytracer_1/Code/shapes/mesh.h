#ifndef MESH_H_
#define MESH_H_

#include "../object.h"
#include "triangle.h"

class Mesh: public Object {
public:
	Mesh(std::string const &model, Point pos, double scale);

	virtual Hit intersect(Ray const &ray);
	
	std::vector<Triangle> faces;
};

#endif
