#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>
#include <iostream>
#include "CRTCamera.h"
#include "CRTMesh.h"
#include "CRTSettings.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include "CRTLight.h"
#include "CRTMaterial.h"

using namespace rapidjson;

class CRTScene {
private:
	std::string sceneFileName; 
	std::vector<CRTMesh> geometryObjects; // here we store the scene objects
	CRTCamera camera; // the camera from which the scene is observed
	CRTSettings settings; //global setting for the scene
	std::vector<CRTLight> lights; //light sources
	std::vector<CRTMaterial> materials; //materials info

	//functions we use in parseSceneFile();
	Document getJsonDocument(const std::string& sceneFileName);

	CRTColor loadColor(const Value::ConstArray& arr);
	CRTVector loadVector(const Value::ConstArray& arr);
	CRTMatrix loadMatrix(const Value::ConstArray& arr);
	std::vector<CRTVector> loadVertices(const Value::ConstArray& arr); 
	std::vector<int> loadTriangles(const Value::ConstArray& arr);  
	CRTColor loadVColor(const Value::ConstArray& arr);


public:
	CRTScene();
	CRTScene(const std::string& sceneFileName);

	const std::vector<CRTMesh>& getGeometryObjects() const;
	const CRTCamera& getCamera() const;
	const CRTSettings& getSettings() const; 
	const std::vector<CRTLight>& getLights() const;
	const std::vector<CRTMaterial> getMaterials() const;

	void parseSceneFile();
};
