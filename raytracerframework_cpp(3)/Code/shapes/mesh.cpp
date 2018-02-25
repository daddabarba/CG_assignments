#include "mesh.h"
#include <cmath>
#include "../objloader.h"
#include <limits>

Hit Mesh::intersect(Ray const &ray)
{
	// iterate through triangles to find closest intersection
	double t = std::numeric_limits<double>::infinity();
	Vector N;
	for (Triangle &face : faces) {
		Hit hit = face.intersect(ray);
		if (hit.t < t) {
			t = hit.t;
			N = hit.N;
		}
	}
	if (t == std::numeric_limits<double>::infinity()) return Hit::NO_HIT();
    return Hit(t, N);
}

Mesh::Mesh(std::string const &model, Point pos, double scale) {
	// convert mesh to triangles and apply translation and scaling
	OBJLoader loader(model);
	std::vector<Vertex> verts = loader.vertex_data();
	for (std::vector<Vertex> ::iterator it = verts.begin(); it < verts.end(); ++it) {
		Vector p0(it->x * scale + pos.x, it->y * scale + pos.y, it->z * scale + pos.z);
		it++;
		Vector p1(it->x * scale + pos.x, it->y * scale + pos.y, it->z * scale + pos.z);
		it++;
		Vector p2(it->x * scale + pos.x, it->y * scale + pos.y, it->z * scale + pos.z);
		Triangle face(p0, p1, p2);
		faces.push_back(face);
	}
}
