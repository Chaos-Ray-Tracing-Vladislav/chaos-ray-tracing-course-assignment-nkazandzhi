#include <fstream>
#include <cmath>

/// Output image resolution
static const int imageWidth = 1280;
static const int imageHeight = 1024;
static const int maxColorComponent = 255;

void draw_rectangules() {

	std::ofstream ppmFileStream("rectangles.ppm", std::ios::out | std::ios::binary); //creates and open the output file

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//the PPM Header
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	//the pixel data
	//aiming for 4 rect in a row and 4 in a col, so one rect will have 320 width and 256 height

	std::srand(std::time(nullptr));

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {

		int rectHeigth = rowIdx / 256; //rectHeight = [0,3]

		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			//ppmFileStream << "0 0 255\t";

			int rectWidth = colIdx / 320; //rectWidth = [0,3]

			int baseColor = (rectWidth + rectHeigth) % 3; //0,1,2

			if (baseColor == 0) {
				// r                                       g                                     b
				ppmFileStream << (rectWidth + 1) * (std::rand() % 80) << " " << std::rand() % 256 << " " << (rectHeigth + 1) * (std::rand() % 80) << " ";
			}
			else if (baseColor == 1) {
				ppmFileStream << (std::rand() % 256) << " " << (rectWidth + 1) * (std::rand() % 80) << " " << (rectHeigth + 1) * (std::rand() % 80) << " ";
			}
			else
			{
				ppmFileStream << (rectHeigth + 1) * (std::rand() % 80) << " " << (rectWidth + 1) * (std::rand() % 80) << " " << (std::rand() % 256) << " ";
			}

		}
		ppmFileStream << "\n";
	}

	ppmFileStream.close(); //closes the file
}

void draw_circle()
{
	std::ofstream ppmFileStream("circle.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	int r = 400; //circle radius

	//the coordinats of the circle
	int rx = imageWidth/2;
	int ry = imageHeight/2;

	for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
		for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
			
			if (sqrt((colIdx - rx) * (colIdx - rx) + (rowIdx - ry) * (rowIdx - ry)) <= r) // is in the circle
			{
				ppmFileStream << "25 25 250\t";
			}
			else
			{
				ppmFileStream << "50 240 25\t";
			}
		}
		ppmFileStream << "\n";
	}
	ppmFileStream.close();


}

int main()
{
	draw_rectangules();
	draw_circle();
}