#include "CRTTriangle.h"

CRTTriangle::CRTTriangle() : verts{ CRTVector(), CRTVector(), CRTVector() }, normal(CRTVector()) {}


void CRTTriangle::find_normal() {
    CRTVector edge1 = verts[1] - verts[0];
    CRTVector edge2 = verts[2] - verts[0];
    normal = edge1.cross(edge2).normalize();
}

CRTTriangle::CRTTriangle(CRTVector v0, CRTVector v1, CRTVector v2) {
    verts[0] = v0;
    verts[1] = v1;
    verts[2] = v2;
    find_normal();
}

std::string CRTTriangle::get_normal()
{
    return normal.to_string();
}


std::string CRTTriangle::to_string() const
{
    return "Vertices:\nv0: " + verts[0].to_string() + "v1: " + verts[1].to_string() + "v2: " + verts[2].to_string() + "\n";
}

float CRTTriangle::get_area() const
{
    CRTVector edge1 = verts[1] - verts[0];
    CRTVector edge2 = verts[2] - verts[0];

    CRTVector cross_product = edge1.cross(edge2);

    float area = 0.5f * cross_product.length(); //triangle area = parallelogram area / 2

    return area; 
}
