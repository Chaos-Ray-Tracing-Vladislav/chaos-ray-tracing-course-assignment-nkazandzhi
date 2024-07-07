#pragma once
#include <string>

class CRTVector {
private:

	float x, y, z; // Direction

public:
	CRTVector();

	CRTVector(float x, float y, float z);

	float length() const;

	CRTVector operator+ (const CRTVector& lhs) const;

	CRTVector operator- (const CRTVector& lhs) const;

	CRTVector operator= (const CRTVector& lhs);

	CRTVector operator*(float scalar) const;

	CRTVector cross(const CRTVector& rhs) const;

	float dot(const CRTVector& rhs) const;

	CRTVector normalize() const;

	std::string to_string() const;
};