#pragma once
#include "CRTVector.h"

const int MATRIX_VAL = 3;

class CRTMatrix {
private:
    float matrix[MATRIX_VAL][MATRIX_VAL]; //row major 3x3 matrix

public:
    CRTMatrix();
    CRTMatrix(float a00, float a01, float a02,
        float a10, float a11, float a12,
        float a20, float a21, float a22);

    friend CRTMatrix operator*(const CRTMatrix& lhs, const CRTMatrix& rhs);
    friend CRTVector operator*(const CRTVector& lhs, const CRTMatrix& rhs);
};