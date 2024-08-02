
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
            float closestT = std::numeric_limits<float>::max();

            for ( auto& mesh : scene.getGeometryObjects()) {
                for ( auto& triangle : mesh.getTriangles()) {
                    triangle.find_normal();
                    float t;
                    if (triangle.intersect(ray, t) && t < closestT) {
                        closestT = t;
                        closestTriangle = const_cast<CRTTriangle*>(&triangle);
                    }
                }
            }

            if (closestTriangle) {
                CRTVector hitPoint = ray.get_hitPoint(closestT);
                CRTColor shadeColor = shade(*closestTriangle, ray, hitPoint);
                image[y][x] = shadeColor;
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

CRTColor CRTRenderer::shade( CRTTriangle& triangle, const CRTRay& ray, const CRTVector& hitPoint) const {
    CRTColor finalColor(0, 0, 0);
    //const CRTColor ALBEDO(0, 0, 150); - used for scene0
    //const CRTColor ALBEDO(150, 0, 150); - used for scene 1
    //const CRTColor ALBEDO(100, 50, 150); - used for scene 2
    const CRTColor ALBEDO(170, 50, 100); // - for scene 3

    CRTVector normal = triangle.get_normal_vector();

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
