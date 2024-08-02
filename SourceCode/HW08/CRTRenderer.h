#pragma once
#include "CRTScene.h"

class CRTRenderer {
private:
	CRTScene scene;


	CRTColor shade( CRTTriangle& triangle, const CRTRay& ray, const CRTVector& hitPoint) const;
	bool intersectsObject(const CRTRay& ray) const;


public:

	CRTRenderer();
	CRTRenderer(CRTScene scene);

	void render(const std::string& outputFileName);

};
