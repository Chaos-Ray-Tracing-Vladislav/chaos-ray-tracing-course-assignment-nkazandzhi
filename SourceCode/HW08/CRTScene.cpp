#include "CRTScene.h"

Document CRTScene::getJsonDocument(const std::string& sceneFileName)
{
	std::ifstream ifs(sceneFileName);
	assert(ifs.is_open());

	IStreamWrapper isw(ifs);
	Document doc;
	doc.ParseStream(isw);

	if (doc.HasParseError()) {
		std::cout << "Error: " << doc.GetParseError() << '\n';
		std::cout << "Offset: " << doc.GetErrorOffset() << '\n';
		assert(false);
	}

	assert(doc.IsObject());
	return doc;
}

CRTColor CRTScene::loadColor(const Value::ConstArray& arr)
{
	assert(arr.Size() == 3);
	CRTColor color{
		static_cast<float>(arr[0].GetDouble()),
		static_cast<float>(arr[1].GetDouble()),
		static_cast<float>(arr[2].GetDouble())
	};

	return color;
}

CRTVector CRTScene::loadVector(const Value::ConstArray& arr)
{
	assert(arr.Size() == 3);
	CRTVector vec{
		static_cast<float>(arr[0].GetDouble()),
		static_cast<float>(arr[1].GetDouble()),
		static_cast<float>(arr[2].GetDouble())
	};

	return vec;
}

CRTMatrix CRTScene::loadMatrix(const Value::ConstArray& arr)
{
	assert(arr.Size() == 9);

	CRTMatrix mat{
		static_cast<float>(arr[0].GetDouble()), static_cast<float>(arr[1].GetDouble()), static_cast<float>(arr[2].GetDouble()),
		static_cast<float>(arr[3].GetDouble()), static_cast<float>(arr[4].GetDouble()), static_cast<float>(arr[5].GetDouble()),
		static_cast<float>(arr[6].GetDouble()), static_cast<float>(arr[7].GetDouble()), static_cast<float>(arr[8].GetDouble())
	};

	return mat;
}

std::vector<CRTVector> CRTScene::loadVertices(const Value::ConstArray& arr)
{
	assert(arr.Size() % 3 == 0);

	std::vector<CRTVector> verts;

	for (SizeType i = 0; i < arr.Size(); i += 3) {
		CRTVector vec{
			static_cast<float>(arr[i].GetDouble()),
			static_cast<float>(arr[i + 1].GetDouble()),
			static_cast<float>(arr[i + 2].GetDouble())
		};

		verts.push_back(vec);
	}


	return verts;
}

std::vector<int> CRTScene::loadTriangles(const Value::ConstArray& arr)
{
	assert(arr.Size() % 3 == 0);

	std::vector<int> triangleIndices;

	for (SizeType i = 0; i < arr.Size(); ++i) {
		int index = arr[i].GetInt();
		triangleIndices.push_back(index);
	}


	return triangleIndices;
}

CRTScene::CRTScene(const std::string& sceneFileName)
{
	this->sceneFileName = sceneFileName;
}

const std::vector<CRTMesh>& CRTScene::getGeometryObjects() const
{
	return this->geometryObjects;
}

const CRTCamera& CRTScene::getCamera() const
{
	return this->camera;
}

const CRTSettings& CRTScene::getSettings() const
{
	return this->settings;
}

const std::vector<CRTLight>& CRTScene::getLights() const
{
	return this->lights;
}


void CRTScene::parseSceneFile()
{
	Document document = getJsonDocument(sceneFileName);

	const Value& settingsVal = document.FindMember("settings")->value;
	if (!settingsVal.IsNull() && settingsVal.IsObject()) {
		const Value& bgColorVal = settingsVal.FindMember("background_color")->value;
		assert(!bgColorVal.IsNull() && bgColorVal.IsArray());
		settings.set_backgroundColor(loadColor(bgColorVal.GetArray()));

		const Value& imageSettingsVal = settingsVal.FindMember("image_settings")->value;
		if (!imageSettingsVal.IsNull() && imageSettingsVal.IsObject()) {
			const Value& imageWidthVal = imageSettingsVal.FindMember("width")->value;
			const Value& imageHeightVal = imageSettingsVal.FindMember("height")->value;
			assert(!imageWidthVal.IsNull() && imageWidthVal.IsInt() && !imageHeightVal.IsNull() && imageHeightVal.IsInt());
			settings.set_width(imageWidthVal.GetInt());
			settings.set_heigth(imageHeightVal.GetInt());
		}
	}

	const Value& cameraVal = document.FindMember("camera")->value;
	if (!cameraVal.IsNull() && cameraVal.IsObject()) {
		const Value& matrixVal = cameraVal.FindMember("matrix")->value;
		assert(!matrixVal.IsNull() && matrixVal.IsArray());
		camera.set_rotationMatrix(loadMatrix(matrixVal.GetArray()));

		const Value& positionVal = cameraVal.FindMember("position")->value;
		assert(!positionVal.IsNull() && positionVal.IsArray());
		camera.set_position(loadVector(positionVal.GetArray()));
	}

	const Value& objectsVal = document.FindMember("objects")->value;
	if (!objectsVal.IsNull() && objectsVal.IsArray()) {
		for (Value::ConstValueIterator itr = objectsVal.Begin();
			itr != objectsVal.End();
			itr++)
		{
			const Value& verticesVal = itr->FindMember("vertices")->value;
			assert(!verticesVal.IsNull() && verticesVal.IsArray());
			std::vector<CRTVector> vertices = loadVertices(verticesVal.GetArray());

			const Value& trianglesVal = itr->FindMember("triangles")->value;
			assert(!trianglesVal.IsNull() && trianglesVal.IsArray());
			std::vector<int> triangles = loadTriangles(trianglesVal.GetArray());

			CRTMesh mesh;
			mesh.set_vertices(vertices);
			mesh.set_triangleVertIndices(triangles);
			mesh.set_triangles(triangles);
			geometryObjects.push_back(mesh);
			
		}
	}

	const Value& ligthsVal = document.FindMember("lights")->value;
	if (!ligthsVal.IsNull() && ligthsVal.IsArray()) {
		for (Value::ConstValueIterator itr = ligthsVal.Begin(); itr != ligthsVal.End(); itr++)
		{
			const Value& intensityVal = itr->FindMember("intensity")->value;
			assert(!intensityVal.IsNull() && intensityVal.IsInt());

			const Value& positionVal = itr->FindMember("position")->value;
			assert(!positionVal.IsNull() && positionVal.IsArray());
			lights.emplace_back(loadVector(positionVal.GetArray()), intensityVal.GetInt());
		}
	}
}
