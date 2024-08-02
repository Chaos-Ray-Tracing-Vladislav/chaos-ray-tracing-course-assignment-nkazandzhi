#include "CRTSettings.h"

CRTSettings::CRTSettings()
{
	width = 50;
	height = 50;
	backgroundColor = CRTColor(0, 0, 0);
	maxColorComponent = 255;
}

CRTSettings::CRTSettings(int width, int height,CRTColor bgColor,int maxColorComp) : width(width), height(height), backgroundColor (bgColor), maxColorComponent(maxColorComp) {}

int CRTSettings::get_width() const
{
	return width;
}

int CRTSettings::get_height() const
{
	return height;
}

int CRTSettings::get_maxColorComponent() const
{
	return maxColorComponent;
}

CRTColor CRTSettings::get_backgroundColor() const
{
	return backgroundColor;
}



void CRTSettings::set_width(int width) 
{
		this->width = width;
}

void CRTSettings::set_heigth(int height)
{
	this->height = height;
}

void CRTSettings::set_maxColorComponent(int max_)
{
	this->maxColorComponent = max_;
}

void CRTSettings::set_backgroundColor(CRTColor bgcolor)
{
	this->backgroundColor = bgcolor;
}


