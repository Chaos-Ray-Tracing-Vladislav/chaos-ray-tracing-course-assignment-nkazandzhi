#pragma once
#include "CRTVector.h"
#include "CRTTriangle.h"
#include <vector>

class CRTMesh {
private:
	std::vector<CRTVector> vertices; // 3D coordinated for the whole mesh
	std::vector<int> triangleVertIndices; // each triple forms a triangle vertices
	std::vector<CRTTriangle> triangles; // the actual triangles of the mesh

public:

	std::vector<CRTVector> get_vertices() const; 
	std::vector<int> get_triangleVertIndices() const;

	void set_vertices(std::vector<CRTVector>& verts);
	void set_triangleVertIndices(std::vector<int>& indices);

	std::vector<CRTTriangle> getTriangles() const;
	void printTriangles() const;
};
