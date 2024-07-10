#include <fstream>
#include "CRTVector.h"
#include <vector>
#include "CRTColor.h"


/// Output image resolution
static const int imageWidth = 200;
static const int imageHeight = 600;
static const int maxColorComponent = 255;

int main() {

    std::ofstream ppmFileStream("hw3.ppm", std::ios::out | std::ios::binary);

    ppmFileStream << "P3\n";
    ppmFileStream << imageWidth << " " << imageHeight << "\n";
    ppmFileStream << maxColorComponent << "\n";

    float aspect_ratio = imageWidth / imageHeight;

    //here we store the colors for each pixel in the image
    std::vector<std::vector<CRTColor>> image(imageHeight, std::vector<CRTColor>(imageWidth, CRTColor(0, 0, 0)));

    for (int x = 0; x < imageWidth; ++x) {
        for (int y = 0; y < imageHeight; ++y) {
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
            float ray_dir_x = screen_x;
            float ray_dir_y = screen_y;
            float ray_dir_z = -1.0f;

            CRTVector ray_dir(screen_x, screen_y, -1.0f);

            // normaling
            ray_dir = ray_dir.normalize();

            // map the direction to color
            int red = static_cast<int>((ray_dir_x * 0.5f + 0.5f) * 255); //shifts the range of x from[-1.0, 1.0] to[0.0, 1.0].
            int green = static_cast<int>((ray_dir_y * 0.5f + 0.5f) * 255);
            int blue = static_cast<int>((ray_dir_z * 0.5f + 0.5f) * 255);

            // Store the color in the image array
            image[y][x] = CRTColor(red, green, blue);
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
