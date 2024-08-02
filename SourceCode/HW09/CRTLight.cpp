#include "CRTLight.h"

CRTLight::CRTLight(const CRTVector& position,const float& intensity)
{
	this->position = position;
	this->intensity = intensity;
}

const CRTVector& CRTLight::get_position() const
{
	return this->position;
}

const float& CRTLight::get_intensity() const
{
	return this->intensity;
}
