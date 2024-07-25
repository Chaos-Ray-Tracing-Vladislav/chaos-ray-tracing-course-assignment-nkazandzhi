#include "CRTRenderer.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <limits>

const float pi = 3.14159265358979323846f;
const float EPSILON = 1e-5;

CRTRenderer::CRTRenderer() : scene("")
{}

CRTRenderer::CRTRenderer(CRTScene scene) : scene(scene) {}

void CRTRenderer::render(const std::string& outputFileName) {
	const auto& settings = scene.getSettings();
	int imageHeight = settings.get_height();
	int imageWidth = settings.get_width();
	int maxColorComponent = settings.get_maxColorComponent();

	std::ofstream ppmFileStream(outputFileName, std::ios::out | std::ios::binary);

	ppmFileStream << "P3\n" << imageWidth << " " << imageHeight << "\n" << maxColorComponent << "\n";

	float aspectRatio = static_cast<float>(imageWidth) / imageHeight;
	std::vector<std::vector<CRTColor>> image(imageHeight, std::vector<CRTColor>(imageWidth, settings.get_backgroundColor()));

	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			float ndc_x = (x + 0.5f) / imageWidth;
			float ndc_y = (y + 0.5f) / imageHeight;

			float screen_x = (2.0f * ndc_x - 1.0f) * aspectRatio;
			float screen_y = 1.0f - 2.0f * ndc_y;

			CRTVector rayDir(screen_x, screen_y, -1.0f);
			rayDir = rayDir * scene.getCamera().get_rotationMatrix();
			rayDir = rayDir.normalize();

			CRTRay ray(scene.getCamera().get_position(), rayDir);

			CRTTriangle* closestTriangle = nullptr;
			int meshIndex;
			float closestT = std::numeric_limits<float>::max();

			for (auto& mesh : scene.getGeometryObjects()) {
				for (auto& triangle : mesh.getTriangles()) {
					
					float t;
					if (triangle.intersect(ray, t) && t < closestT) {
						closestT = t;
						closestTriangle = const_cast<CRTTriangle*>(&triangle);
						meshIndex = mesh.get_meshIndex();
					}
				}
			}

			if (closestTriangle) {
				//if we get here we have found intersection with the closest triangle

				CRTColor shadeColor;

				//check the material of the triangle based on the mesh Index
				if(scene.getMaterials()[meshIndex].type == CRTMaterial::CRTMaterialType::DIFFUSE){
				
					//the triangle has diffuse material
					CRTVector hitPoint = ray.get_hitPoint(closestT);
					shadeColor = shade(*closestTriangle, ray, hitPoint, meshIndex);
					
				}
				else if (scene.getMaterials()[meshIndex].type == CRTMaterial::CRTMaterialType::REFLECTIVE)
				{
					//the triangle has reflective material
					CRTVector normal = closestTriangle->get_normal_vector();
					CRTVector hitPoint = ray.get_hitPoint(closestT);
					CRTVector reflectionDir = ray.get_direction() - (normal * normal.dot(ray.get_direction()) * 2.0f);
					reflectionDir = reflectionDir.normalize();
					CRTRay reflectionRay(hitPoint + normal * EPSILON, reflectionDir);
					shadeColor = trace(reflectionRay);
					
				}
				else{
					
					shadeColor = settings.get_backgroundColor();
					
				}
				
				// store the color in the image array
				image[y][x] = shadeColor;

				// this is task 1 
				//CRTVector hitPoint = ray.get_hitPoint(closestT);
				//image[y][x] = closestTriangle->color_based_on_barycentric(hitPoint);
			}
			else {
				image[y][x] = settings.get_backgroundColor();
			}
		}
	}

	for (const auto& row : image) {
		for (const auto& color : row) {
			ppmFileStream << color.getColor() << " ";
		}
		ppmFileStream << "\n";
	}
}

CRTColor CRTRenderer::shade(const CRTTriangle& triangle, const CRTRay& ray, const CRTVector& hitPoint, const int& meshIndex) const {
	CRTColor finalColor(0, 0, 0);
	CRTColor ALBEDO = scene.getMaterials()[meshIndex].albedo;

	CRTVector normal = triangle.get_normal_vector();

	if (scene.getMaterials()[meshIndex].smooth_shading)
	{
		float u = 0;
		float v = 0;
		CRTVector v0p = hitPoint - triangle.get_vert0();
		CRTVector v0v1 = triangle.get_vert1() - triangle.get_vert0();
		CRTVector v0v2 = triangle.get_vert2() - triangle.get_vert0();
		float area = (float)((v0v1 * v0v2).length());
		u = (float)((float)(v0p * v0v2).length() / area);
		v = (float)((float)(v0v1 * v0p).length() / area);

		normal = triangle.get_vert1().normalize() * u + triangle.get_vert2().normalize() * v + triangle.get_vert0().normalize() * (1 - u - v);
		normal = normal.normalize();	

	}

	for (const auto& light : scene.getLights()) {
		CRTVector lightDir = (light.get_position() - hitPoint).normalize();
		float lightDistance = (light.get_position() - hitPoint).length();
		CRTRay shadowRay(hitPoint + normal * EPSILON, lightDir);

		bool shadowed = intersectsObject(shadowRay);

		if (!shadowed) {
			float intensity = std::max(0.0f, normal.dot(lightDir)) * (light.get_intensity() / (4 * pi * lightDistance * lightDistance));
			finalColor = finalColor + ALBEDO * intensity;
		}
	}

	return finalColor;
}

bool CRTRenderer::intersectsObject(const CRTRay& ray) const
{
	for (auto mesh : scene.getGeometryObjects()) {
		for (const auto& triangle : mesh.getTriangles()) {
			float t;
			if (triangle.intersect(ray, t)) {
				return true;
			}
		}
	}
	return false;

}

CRTColor CRTRenderer::trace(const CRTRay& ray) const {
	CRTTriangle* closestTriangle = nullptr;
	int meshIndex;
	float closestT = std::numeric_limits<float>::max();

	for (auto& mesh : scene.getGeometryObjects()) {
		for (auto& triangle : mesh.getTriangles()) {
			float t;
			if (triangle.intersect(ray, t) && t < closestT) {
				closestT = t;
				closestTriangle = const_cast<CRTTriangle*>(&triangle);
				meshIndex = mesh.get_meshIndex();
			}
		}
	}

	if (closestTriangle) {
		CRTVector hitPoint = ray.get_hitPoint(closestT);
		switch (scene.getMaterials()[meshIndex].type) {
		case CRTMaterial::CRTMaterialType::DIFFUSE:
			return shade(*closestTriangle, ray, hitPoint, meshIndex);
		case CRTMaterial::CRTMaterialType::REFLECTIVE: {
			CRTVector normal = closestTriangle->get_normal_vector();
			CRTVector reflectionDir = ray.get_direction() - (normal * normal.dot(ray.get_direction()) * 2.0f);
			reflectionDir = reflectionDir.normalize();
			CRTRay reflectionRay(hitPoint + normal * EPSILON, reflectionDir);
			return trace(reflectionRay);
		}
		default:
			return scene.getSettings().get_backgroundColor();
		}
	}

	return scene.getSettings().get_backgroundColor()+CRTColor(20,20,20);
}