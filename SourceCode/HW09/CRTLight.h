#pragma once
#include "CRTVector.h"

class CRTLight {
private:
	CRTVector position; //light position
	float intensity; 
public:
	CRTLight(const CRTVector& position, const float& intensity);

	const CRTVector& get_position() const;

	const float& get_intensity() const;
};
