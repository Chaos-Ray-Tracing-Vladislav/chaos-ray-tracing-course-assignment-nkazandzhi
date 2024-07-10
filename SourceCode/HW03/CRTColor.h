#pragma once
#include <string>

class CRTColor {

private:
	float red;
	float green;
	float blue;
public:

	CRTColor();

	CRTColor(float red, float green, float blue);

	std::string getColor() const;
};
