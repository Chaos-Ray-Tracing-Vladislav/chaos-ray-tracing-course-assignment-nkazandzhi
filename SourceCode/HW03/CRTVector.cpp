#include "CRTVector.h"
#include "Math.h"
#include "string"

CRTVector::CRTVector()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

CRTVector::CRTVector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float CRTVector::length() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

CRTVector CRTVector::operator+(const CRTVector& lhs) const
{
	return CRTVector{ x + lhs.x,y + lhs.y,z + lhs.z };
}


CRTVector CRTVector::operator-(const CRTVector& lhs) const
{
	return CRTVector{ x - lhs.x,y - lhs.y,z - lhs.z };
}

CRTVector CRTVector::operator=(const CRTVector& lhs)
{
	if (this == &lhs) {
		return *this; 
	}
	x = lhs.x;
	y = lhs.y;
	z = lhs.z;
	return *this;
}

CRTVector CRTVector::cross(const CRTVector& rhs) const
{
	return CRTVector{
		y * rhs.z - z * rhs.y,
		z * rhs.x - x * rhs.z,
		x * rhs.y - y * rhs.x

	};
}

float CRTVector::dot(const CRTVector& rhs) const
{
	return ((x * rhs.x) + (y * rhs.y) + (z * rhs.z));
}

CRTVector CRTVector::normalize() const
{
	int length = this->length();

	if (length == 0) {
		return CRTVector(0, 0, 0); 
	}

	return CRTVector(this->x / length, this->y / length, this->z / length);
}

std::string CRTVector::to_string() const
{
	return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ")\n";
}
