#include <fstream>
#include "CRTVector.h"
#include "CRTRay.h"
#include <vector>
#include "CRTColor.h"
#include <iostream>

#include "CRTTriangle.h"
#include "CRTCamera.h"
#include "CRTScene.h"
#include "CRTRenderer.h"

int main()
{
	std::string sceneFilePath = "scene3.crtscene";

	CRTScene scene0(sceneFilePath);
	scene0.parseSceneFile();

	CRTRenderer render(scene0);
	render.render("scene3.ppm");


	return 0;
}