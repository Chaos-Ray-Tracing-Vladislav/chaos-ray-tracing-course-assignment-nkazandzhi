#pragma once
#include "CRTColor.h";

class CRTSettings {
private:
	
	int width;
	int height;

	CRTColor backgroundColor;
	int maxColorComponent;


public:
	CRTSettings();
	CRTSettings(int width, int height, CRTColor bgColor, int maxColorComponent = 255);

	int get_width() const;
	int get_height() const;
	int get_maxColorComponent() const;
	CRTColor get_backgroundColor() const; 

	void set_width(int width);
	void set_heigth(int height); 
	void set_maxColorComponent(int max_);
	void set_backgroundColor(CRTColor bgcolor);

};
