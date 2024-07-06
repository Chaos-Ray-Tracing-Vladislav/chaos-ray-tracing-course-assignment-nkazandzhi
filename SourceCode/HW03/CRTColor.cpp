#include "CRTColor.h"

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


