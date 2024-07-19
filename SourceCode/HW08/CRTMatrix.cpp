#include "CRTMatrix.h"

CRTMatrix::CRTMatrix() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0f;
        }
    }
}

CRTMatrix::CRTMatrix(float a00, float a01, float a02,
    float a10, float a11, float a12,
    float a20, float a21, float a22) {
    matrix[0][0] = a00; matrix[0][1] = a01; matrix[0][2] = a02;
    matrix[1][0] = a10; matrix[1][1] = a11; matrix[1][2] = a12;
    matrix[2][0] = a20; matrix[2][1] = a21; matrix[2][2] = a22;
}

// Matrix multiplication
CRTMatrix operator*(const CRTMatrix& lhs, const CRTMatrix& rhs) {
    CRTMatrix result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.matrix[i][j] = 0.0f;
            for (int k = 0; k < 3; ++k) {
                result.matrix[i][j] += lhs.matrix[i][k] * rhs.matrix[k][j];
            }
        }
    }
    return result;
}

// Vector-matrix multiplication
CRTVector operator*(const CRTVector& lhs, const CRTMatrix& rhs) {
    CRTVector result;
    result.set_x(lhs.get_x() * rhs.matrix[0][0] + lhs.get_y() * rhs.matrix[1][0] + lhs.get_z() * rhs.matrix[2][0]);
    result.set_y(lhs.get_x() * rhs.matrix[0][1] + lhs.get_y() * rhs.matrix[1][1] + lhs.get_z() * rhs.matrix[2][1]);
    result.set_z(lhs.get_x() * rhs.matrix[0][2] + lhs.get_y() * rhs.matrix[1][2] + lhs.get_z() * rhs.matrix[2][2]);
    return result;
}