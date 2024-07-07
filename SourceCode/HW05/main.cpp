#include <fstream>
#include "CRTVector.h"
#include "CRTRay.h"
#include <vector>
#include "CRTColor.h"
#include <iostream>
#include "CRTTriangle.h"

static const int imageWidth = 550;
static const int imageHeight = 550;
static const int maxColorComponent = 255;

int main()
{
    std::ofstream ppmFileStream("pyramid.ppm", std::ios::out | std::ios::binary);

    ppmFileStream << "P3\n";
    ppmFileStream << imageWidth << " " << imageHeight << "\n";
    ppmFileStream << maxColorComponent << "\n";

    float aspect_ratio = static_cast<float>(imageWidth) / imageHeight;

    //triangle definitions
    CRTTriangle tri1({ -1, 0, -3 }, { -1.5, -1, -3.5 }, { -0.5, -1, -3.5 });

    CRTTriangle tri2({ -1, 0, -3 }, { -0.5, -1, -3.5 }, { -0.5, -1, -2.5 });

    CRTTriangle tri3({ -1, -0, -3 }, { -0.5, -1, -2.5 }, { -1.5, -1, -2.5 });

    CRTTriangle tri4({ -1, 0, -3 }, { -1.5, -1, -2.5 }, { -1.5, -1, -3.5 });


    std::vector<CRTTriangle> triangles = { tri1, tri2, tri3, tri4 };

    std::vector<std::vector<CRTColor>> image(imageHeight, std::vector<CRTColor>(imageWidth, CRTColor(0, 0, 0)));

    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            // find the center of the pixel in raster space
            float raster_x = x + 0.5f;
            float raster_y = y + 0.5f;

            // convert to NDC space
            float ndc_x = raster_x / imageWidth;
            float ndc_y = raster_y / imageHeight;

            // convert to screen space
            float screen_x = 2.0f * ndc_x - 1.0f;
            float screen_y = 1.0f - 2.0f * ndc_y;

            // adjust for aspect ratio
            screen_x *= aspect_ratio;

            // ray direction in screen space
            CRTVector ray_dir(screen_x, screen_y, -1.0f);
            ray_dir = ray_dir.normalize();

            CRTRay ray(CRTVector(0, 0, 0), ray_dir);

            // check for intersection with any triangle
            bool intersected = false;
            for (const auto& triangle : triangles) {
                float t = 0;
                if (triangle.intersects(ray, t)) {
                    intersected = true;
                    //if (triangle == tri) { let it be blue; } else if (triangle == triangle2) { green; }
                    int red = static_cast<int>((screen_x * 0.5f + 0.5f) * 255); // Adjusted for green-yellow
                    int green = static_cast<int>((screen_y * 0.5f + 0.5f) * 255); // Adjusted for green-yellow
                    int blue = 0; // Lower blue value for green-yellowish color


                    // store the color in the image array
                    image[y][x] = CRTColor(red, green, blue); //I'm current strugglung with coloring the different triangles with different colors
                    
                      
                    break; // Exit loop once we find an intersection
                }
            }

            if (!intersected) {
                image[y][x] = CRTColor(0, 50, 255); // Blue color for no intersection
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
    return 0;
}

//Coordinates for HW05_3
//CRTTriangle tri({ 0, 0, -3 }, { 1, 0, -3 }, { 0, 1, -3 });
//CRTTriangle another_tri({ -2,-1,-3 }, { 0, -1, -2 }, { -1, 1, -2 });