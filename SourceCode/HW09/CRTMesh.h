#pragma once
#include "CRTVector.h"
#include "CRTTriangle.h"
#include <vector>
#include "CRTMaterial.h"
#include <tuple>

class CRTMesh {
private:
	std::vector<CRTVector> vertices; // 3D coordinated for the whole mesh
	std::vector<int> triangleVertIndices; // each triple forms a triangle vertices
	std::vector<CRTTriangle> triangles; // the actual triangles of the mesh
	int meshInd = -1;

	void createTriangles();
	void addTriangle(const CRTTriangle& triangle);

public:
	CRTMesh();

	//get functions
	std::vector<CRTVector> get_vertices() const; 
	std::vector<int> get_triangleVertIndices() const;
	std::vector<CRTTriangle> getTriangles() const;
	int get_meshIndex() const;

	//set functions
	void set_vertices(std::vector<CRTVector>& verts);
	void set_triangleVertIndices(std::vector<int>& indices);
	void set_triangles(const std::vector<int>& indices);
	void set_meshInd(int index);
		
	void printTriangles() const;
		
	
};
