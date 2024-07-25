#include "CRTVector.h"
#include "Math.h"
#include "string"
#include <assert.h>

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
	return sqrt((x * x) + (y * y) + (z * z));
}

CRTVector CRTVector::operator+(const CRTVector& lhs) const
{
	return CRTVector{ x + lhs.x,y + lhs.y,z + lhs.z };
}


CRTVector CRTVector::operator-(const CRTVector& lhs) const
{
	return CRTVector{ (float)x - lhs.x,(float)y - lhs.y,(float)z - lhs.z };
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

CRTVector CRTVector::operator*(float scalar) const
{

	return CRTVector(x * scalar, y * scalar, z * scalar);

}

CRTVector CRTVector::operator*(const CRTVector& other) const
{
	return {this->get_y() * other.get_z() - this->get_z() * other.get_y(),
			this->get_z()* other.get_x() - this->get_x() * other.get_z(),
			this->get_x()* other.get_y() - this->get_y() * other.get_x()};
}

CRTVector CRTVector::operator/(const float& scalar)
{
	if (scalar == 0) {
		return CRTVector(0,0,0);
	}
	return CRTVector(x / scalar, y / scalar, z / scalar);
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
	float length = this->length();

	if (length == 0) {
		return CRTVector(0, 0, 0);
	}
	float devLength = 1.0f / length;
	return CRTVector(this->x * devLength, this->y * devLength, this->z * devLength);
}

std::string CRTVector::to_string() const
{
	return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ", " + std::to_string(this->z) + ")\n";
}

float CRTVector::get_x() const
{
	return x;
}

float CRTVector::get_y() const
{
	return y;
}

float CRTVector::get_z() const
{
	return z;
}

void CRTVector::set_x(float x)
{
	this->x = x;
}

void CRTVector::set_y(float y)
{
	this->y = y;
}

void CRTVector::set_z(float z)
{
	this->z = z;
}



