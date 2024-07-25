#include "CRTTriangle.h"
#include <iostream>

CRTTriangle::CRTTriangle() : verts{ CRTVector(), CRTVector(), CRTVector() }, normal(CRTVector()) {}


void CRTTriangle::find_normal() {
	CRTVector edge1 = verts[1] - verts[0];
	CRTVector edge2 = verts[2] - verts[0];
	this->normal = edge1.cross(edge2).normalize();
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


CRTVector CRTTriangle::get_normal_vector() const
{
	return normal;
}


CRTVector CRTTriangle::get_vert0() const {

    return verts[0];
}

CRTVector CRTTriangle::get_vert1() const
{
    return verts[1];
}

CRTVector CRTTriangle::get_vert2() const
{
    return verts[2];
}


CRTColor CRTTriangle::color_based_on_barycentric(CRTVector hitPoint) const
{
    CRTVector v0 = this->get_vert1() - this->get_vert0();
    CRTVector v1 = this->get_vert2() - this->get_vert0();
    CRTVector v2 = hitPoint - this->get_vert0();

    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    float denom = d00 * d11 - d01 * d01;

    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;

    // interpolate vertex colors using barycentric coordinates
    CRTColor color0(255, 0, 0);
    CRTColor color1(0, 255, 0);
    CRTColor color2(0, 0, 255);

    int red = static_cast<int>(u * color0.get_red() + v * color1.get_red() + w * color2.get_red());
    int green = static_cast<int>(u * color0.get_green() + v * color1.get_green() + w * color2.get_green());
    int blue = static_cast<int>(u * color0.get_blue() + v * color1.get_blue() + w * color2.get_blue());

    return CRTColor(red, green, blue);
}


float CRTTriangle::get_area() const
{
	CRTVector edge1 = verts[1] - verts[0];
	CRTVector edge2 = verts[2] - verts[0];

	CRTVector cross_product = edge1.cross(edge2);

	float area = 0.5f * cross_product.length(); //triangle area = parallelogram area / 2

	return area;
}

CRTTriangle CRTTriangle::operator=(const CRTTriangle& lhs)
{
    if (this == &lhs)
        return *this;

    for (int i = 0; i < vertsInTriangle; ++i)
    {
        verts[i] = lhs.verts[i];
    }

    normal = lhs.normal;

    return *this;
}

bool CRTTriangle::intersect(const CRTRay& ray, float& t) const {
    const float epsilon = 1e-6;

    CRTVector vertex0 = verts[0];
    CRTVector vertex1 = verts[1];
    CRTVector vertex2 = verts[2];

    CRTVector edge1 = vertex1 - vertex0;
    CRTVector edge2 = vertex2 - vertex0;

    CRTVector rayOrigin = ray.get_origin();
    CRTVector rayDirection = ray.get_direction();

    // compute the plane's normal
    CRTVector normal = edge1.cross(edge2);
    float area2 = normal.length();

    //finding P

    // check if the ray and plane are parallel
    float normalDotRayDirection = normal.dot(rayDirection);
    if (fabs(normalDotRayDirection) < epsilon) {
        return false; // Ray is parallel to the triangle
    }

    // compute d parameter using the plane equation
    float d = -normal.dot(vertex0);

    // compute t (intersection distance)
    t = -(normal.dot(rayOrigin) + d) / normalDotRayDirection;

    // check if the triangle is behind the ray
    if (t < 0) {
        return false; // Triangle is behind the ray
    }

    // compute the intersection point P
    CRTVector P = rayOrigin + rayDirection * t;

    // inside-Outside Test
    CRTVector C; // Vector perpendicular to triangle's plane

    // edge 0
    CRTVector edge0 = vertex1 - vertex0;
    CRTVector vp0 = P - vertex0;
    C = edge0.cross(vp0);
    if (normal.dot(C) < 0) {
        return false; // P is on the right side
    }

    // edge 1
    CRTVector edge4 = vertex2 - vertex1;
    CRTVector vp1 = P - vertex1;
    C = edge4.cross(vp1);
    if (normal.dot(C) < 0) {
        return false; // P is on the right side
    }

    // edge 2
    CRTVector edge5 = vertex0 - vertex2;
    CRTVector vp2 = P - vertex2;
    C = edge5.cross(vp2);
    if (normal.dot(C) < 0) {
        return false; // P is on the right side
    }

    return true; // this ray hits the triangle
}


