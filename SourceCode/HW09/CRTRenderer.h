#pragma once
#include "CRTScene.h"

class CRTRenderer {
private:
	CRTScene scene;
		
	CRTColor shade(const CRTTriangle& triangle, const CRTRay& ray, const CRTVector& hitPoint, const int& meshIndex) const;

	bool intersectsObject(const CRTRay& ray) const;

	CRTColor trace(const CRTRay& ray) const;


public:

	CRTRenderer();
	CRTRenderer(CRTScene scene);

	void render(const std::string& outputFileName);

};
