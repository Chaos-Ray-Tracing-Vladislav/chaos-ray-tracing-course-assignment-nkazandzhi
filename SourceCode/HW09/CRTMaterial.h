#pragma once
#include "CRTVector.h"
#include "CRTColor.h"

class CRTMaterial
{
public:

	enum CRTMaterialType
	{
		DIFFUSE,
		REFLECTIVE
	};
	CRTColor albedo;
	bool smooth_shading;
	CRTMaterialType type;

	CRTMaterial() {
		type = CRTMaterialType(0);
		albedo = CRTColor();
		smooth_shading = 0;
	}
};

