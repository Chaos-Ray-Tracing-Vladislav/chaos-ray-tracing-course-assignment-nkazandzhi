#include "CRTRay.h"


CRTRay::CRTRay()
{
	this->origin = CRTVector();
	this->direction = CRTVector();
}

CRTRay::CRTRay(CRTVector origin, CRTVector direction)
{
	this->origin = origin;
	this->direction = direction;
	direction.normalize();
}

CRTVector CRTRay::get_origin() const
{
	return this->origin;
}

CRTVector CRTRay::get_direction() const
{
	return this->direction;
}

CRTVector CRTRay::get_hitPoint(float t) const
{
	return (origin + ( direction * t));
}

