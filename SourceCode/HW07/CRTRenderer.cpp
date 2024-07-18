#include "CRTRenderer.h"

CRTRenderer::CRTRenderer() : scene("")
{}

CRTRenderer::CRTRenderer(CRTScene scene) : scene(scene) {
}

void CRTRenderer::render(const std::string outputFileName)
{
	int imageHeight = scene.getSettings().get_height();
	int imageWidth = scene.getSettings().get_width();

	std::ofstream ppmFileStream(outputFileName, std::ios::out | std::ios::binary);

	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << scene.getSettings().get_maxColorComponent() << "\n";

	float aspect_ratio = static_cast<float>(imageWidth) / imageHeight;

	std::vector<std::vector<CRTColor>> image(imageHeight, std::vector<CRTColor>(imageWidth, CRTColor(0, 0, 0)));

	std::vector<CRTColor> colors = {
	CRTColor(255, 0, 0),    // red
	CRTColor(0, 255, 0),    // green
	CRTColor(0, 0, 255),    // blue
	CRTColor(255, 255, 0),  // yellow
	//CRTColor(245, 158, 66),  // orange
	CRTColor(175, 66, 245),   // purple
	CRTColor(245, 132, 219), // pink
	CRTColor(179, 245, 132)   // greenish
	};

	for (int y = 0; y < imageHeight; ++y) {
		for (int x = 0; x < imageWidth; ++x) {
			// find the center of the pixel in raster space
			float raster_x = x + 0.5f;
			float raster_y = y + 0.5f;

			// convert to NDC space
			float ndc_x = raster_x / imageWidth;
			float ndc_y = raster_y / imageHeight;

			// convert to screen space, [-1,1]
			float screen_x = 2.0f * ndc_x - 1.0f;
			float screen_y = 1.0f - 2.0f * ndc_y;

			// adjust for aspect ratio
			screen_x *= aspect_ratio;

			// ray direction in screen space
			CRTVector ray_dir(screen_x, screen_y, -1.0f);
			ray_dir = ray_dir * scene.getCamera().get_rotationMatrix();
			ray_dir = ray_dir.normalize();

			CRTRay ray(scene.getCamera().get_position(), ray_dir);
			

			// check for intersection with any triangle
			bool intersected = false;
			int triangleIndex = 0;
			for (auto mesh : scene.getGeometryObjects()) {
				for (const auto& triangle : mesh.getTriangles()) {
					float t = 0;
					if (triangle.intersects(ray, t)) {
						intersected = true;

						CRTColor color = colors[triangleIndex % colors.size()];
						image[y][x] = color;

						break; // exit loop once we find an intersection
					}
					++triangleIndex;
				}
			}

			if (!intersected) {
				image[y][x] = scene.getSettings().get_backgroundColor(); //background color for no intersection
			}
		}
	}

	for (const auto& row : image) {
		for (const auto& pixel : row) {
			ppmFileStream << pixel.getColor();
		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close();
}
