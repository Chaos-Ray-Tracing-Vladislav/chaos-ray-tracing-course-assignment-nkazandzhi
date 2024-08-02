#pragma once
#include "CRTScene.h"

class CRTRenderer {
private:
	CRTScene scene;
public:

	CRTRenderer();
	CRTRenderer(CRTScene scene);

	void render(const std::string fileName);
};
