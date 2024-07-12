#include <fstream>
#include "CRTVector.h"
#include "CRTRay.h"
#include <vector>
#include "CRTColor.h"
#include <iostream>
#include "CRTTriangle.h"
#include "CRTCamera.h"

static const int imageWidth = 550;
static const int imageHeight = 550;
static const int maxColorComponent = 255;

int main()
{ 
    for (int i = 0; i <= 25; i++) {
        std::ofstream ppmFileStream("animation" + std::to_string(i) + ".ppm", std::ios::out | std::ios::binary);

        ppmFileStream << "P3\n";
        ppmFileStream << imageWidth << " " << imageHeight << "\n";
        ppmFileStream << maxColorComponent << "\n";

        float aspect_ratio = static_cast<float>(imageWidth) / imageHeight;

        //triangle definitions for pyramid
        CRTTriangle tri1({ -1, 0, -3 }, { -1.5, -1, -3.5 }, { -0.5, -1, -3.5 });

        CRTTriangle tri2({ -1, 0, -3 }, { -0.5, -1, -3.5 }, { -0.5, -1, -2.5 });

        CRTTriangle tri3({ -1, -0, -3 }, { -0.5, -1, -2.5 }, { -1.5, -1, -2.5 });

        CRTTriangle tri4({ -1, 0, -3 }, { -1.5, -1, -2.5 }, { -1.5, -1, -3.5 });

        //CRTTriangle triangle({ -1.75, -1.75, -3 }, { 1.75, -1.75, -3 }, { 0, 1.75, -3 }); // Task 2 triangle

        std::vector<CRTTriangle> triangles = { tri1, tri2, tri3, tri4 };

        // std::vector<CRTTriangle> triangles = { triangle };

        std::vector<std::vector<CRTColor>> image(imageHeight, std::vector<CRTColor>(imageWidth, CRTColor(0, 0, 0)));

        CRTCamera camera(CRTVector(0, 0, 1)); // camera at position (0 0 1)

        //camera.pan(30); // pan the camera by 30 deg  -  Task 1 
        //camera.tilt(45); //tilt the camera by 45 deg - Task 3
        //camera.roll(-35); // - Task 3
        //camera.truck(CRTVector(-3, 1, 1)); // - Task 3
        //camera.dolly(CRTVector(1, 1, 4)); // - Task 3
        //camera.pedestal(CRTVector(1, -3, 2)); // - Task 3

        //Task 4
        //camera.tilt(45);
        //camera.dolly(CRTVector(1, 1, 4));
        //camera.truck(CRTVector(-3, 1, 1));

        //Task 5
        camera.pan(i*5);

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
                ray_dir = ray_dir * camera.get_rotationMatrix();
                ray_dir = ray_dir.normalize();

                CRTRay ray(camera.get_position(), ray_dir);


                // check for intersection with any triangle
                bool intersected = false;
                for (const auto& triangle : triangles) {
                    float t = 0;
                    if (triangle.intersects(ray, t)) {
                        intersected = true;
                        int red = static_cast<int>((screen_x * 1.2f + 0.5f) * 255);
                        int green = 0;
                        int blue = static_cast<int>((screen_y * 0.5f + 0.5f) * 255);


                        // store the color in the image array
                        image[y][x] = CRTColor(red, green, blue);


                        break; // Exit loop once we find an intersection
                    }
                }

                if (!intersected) {
                    image[y][x] = CRTColor(255, 155, 55); //Orange color for no intersection
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
    return 0;
}
