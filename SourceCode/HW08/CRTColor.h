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

	CRTColor operator*(float scalar) const;
	CRTColor operator+(const CRTColor& other) const;
	CRTColor operator=(const CRTColor& other);
	CRTColor operator*(const CRTColor& other);

};
