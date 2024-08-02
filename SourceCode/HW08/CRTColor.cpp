#include "CRTColor.h"
#include <algorithm>

CRTColor::CRTColor()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;

}

CRTColor::CRTColor(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

std::string CRTColor::getColor() const
{
	return (std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue) + " ");
}

CRTColor CRTColor::operator*(float scalar) const
{

	return CRTColor(red * scalar, green * scalar, blue * scalar);
}

CRTColor CRTColor::operator+(const CRTColor& other) const
{
	
		return CRTColor(red + other.red, green + other.green, blue + other.blue);
	
}

CRTColor CRTColor::operator=(const CRTColor& other)
{
	if (this == &other) {
		return *this;
	}
	this->red = other.red;
	this->green = other.green;
	this->blue = other.blue;

	return *this;

}

CRTColor CRTColor::operator*(const CRTColor& other)
{
	return CRTColor(red * other.red, green * other.green, blue * other.blue);
}
