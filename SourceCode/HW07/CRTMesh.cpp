#include "CRTMesh.h"
#include <iostream>

std::vector<CRTVector> CRTMesh::get_vertices() const
{
    return vertices;
}

std::vector<int> CRTMesh::get_triangleVertIndices() const
{
    return this->triangleVertIndices;
}

void CRTMesh::set_vertices(std::vector<CRTVector>& verts)
{
    this->vertices = verts;
}

void CRTMesh::set_triangleVertIndices(std::vector<int>& indices)
{
    this->triangleVertIndices = indices;
}

std::vector<CRTTriangle> CRTMesh::getTriangles() const
{
    std::vector<CRTTriangle> triangles;
    for (size_t i = 0; i < triangleVertIndices.size(); i += 3) {
        CRTVector v0 = vertices[triangleVertIndices[i]];
        CRTVector v1 = vertices[triangleVertIndices[i + 1]];
        CRTVector v2 = vertices[triangleVertIndices[i + 2]];
        triangles.emplace_back(v0, v1, v2);
    }
    return triangles;
}


void CRTMesh::printTriangles() const {
    for (size_t i = 0; i < triangleVertIndices.size(); i += 3) {
        CRTVector v0 = vertices[triangleVertIndices[i]];
        CRTVector v1 = vertices[triangleVertIndices[i + 1]];
        CRTVector v2 = vertices[triangleVertIndices[i + 2]];
        std::cout << "Triangle " << i / 3 << ": (" << v0.to_string() << "), (" << v1.to_string() << "), (" << v2.to_string() << ")" << std::endl;
    }
}



