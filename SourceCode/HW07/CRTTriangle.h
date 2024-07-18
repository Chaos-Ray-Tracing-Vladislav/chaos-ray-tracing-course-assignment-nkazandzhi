#pragma once

#include "CRTVector.h"
#include "CRTRay.h"

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
	void find_normal();
	std::string to_string() const;
	float get_area() const;
	bool intersects(const CRTRay& ray, float& t) const;


};