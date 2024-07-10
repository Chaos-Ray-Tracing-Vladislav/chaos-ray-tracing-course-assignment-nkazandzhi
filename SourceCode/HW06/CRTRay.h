#pragma once

#include "CRTVector.h"

class CRTRay
{
private:

	CRTVector origin;
	CRTVector direction;

public:

	CRTRay();
	CRTRay(CRTVector origin, CRTVector direction);

	CRTVector get_origin() const;
	CRTVector get_direction() const;
	CRTVector get_hitPoint(float t) const; //to find exactly the hit point in 3D space
	//void normalize();
};
