#pragma once

#include "CRTVector.h"
#include "CRTRay.h"
#include "CRTColor.h"
#include "CRTMaterial.h"

static const int vertsInTriangle = 3;

class CRTTriangle
{
private:
	CRTVector verts[vertsInTriangle]; // verts in counterclockwise order
	CRTVector normal; // perpendicular unit vector to the triangle's plane 

public:
	CRTTriangle();
	CRTTriangle(CRTVector v0, CRTVector v1, CRTVector v2);

	std::string get_normal();
	CRTVector get_normal_vector() const;
	std::string to_string() const;

	
	CRTVector get_vert0() const;
	CRTVector get_vert1() const;
	CRTVector get_vert2() const;
	
	CRTColor color_based_on_barycentric(CRTVector hitPoint) const;

	void find_normal();
	float get_area() const;

	bool intersect(const CRTRay& ray, float& t) const;


	CRTTriangle operator= (const CRTTriangle& lhs);

};
