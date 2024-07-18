#include "CRTCamera.h"

static const float pi = 3.14159265358979323846f;

CRTCamera::CRTCamera() : position(), rotationMatrix() {}

CRTCamera::CRTCamera(CRTVector position)
{
    this->position = position;
    this->rotationMatrix = CRTMatrix(1,0,0,0,1,0,0,0,1);
}

void CRTCamera::truck(const CRTVector& moveDir) {
    CRTVector moveDirInWorldSpace = moveDir * rotationMatrix;
    position = position + moveDirInWorldSpace;
}

void CRTCamera::dolly(const CRTVector& moveDir) {
    CRTVector moveDirInWorldSpace = moveDir * rotationMatrix;
    position = position + moveDirInWorldSpace;
}

void CRTCamera::pedestal(const CRTVector& moveDir) {
    CRTVector moveDirInWorldSpace = moveDir * rotationMatrix;
    position = position + moveDirInWorldSpace;
}

void CRTCamera::pan(const float degs) {
    const float rads = degs * (pi / 180.f);
    CRTMatrix rotateAroundY{
        cosf(rads), 0.f, -sinf(rads),
        0.f, 1.f, 0.f,
        sinf(rads), 0.f, cosf(rads)
    };
    
   rotationMatrix = rotationMatrix * rotateAroundY;
}

void CRTCamera::tilt(const float degs) {
    const float rads = degs * (pi / 180.f);
    CRTMatrix rotateAroundX{
        1.f, 0.f, 0.f,
        0.f, cosf(rads), -sinf(rads),
        0.f, sinf(rads), cosf(rads)
    };
    rotationMatrix = rotationMatrix * rotateAroundX;
}

void CRTCamera::roll(const float degs) {
    const float rads = degs * (pi / 180.f);
    CRTMatrix rotateAroundZ{
        cosf(rads), -sinf(rads), 0.f,
        sinf(rads), cosf(rads), 0.f,
        0.f, 0.f, 1.f
    };
    rotationMatrix = rotationMatrix * rotateAroundZ;
}

CRTVector CRTCamera::get_position() const
{
    return this->position;
}

CRTMatrix CRTCamera::get_rotationMatrix() const
{
    return this->rotationMatrix;
}

void CRTCamera::set_position(CRTVector position)
{
    this->position = position;
}

void CRTCamera::set_rotationMatrix(CRTMatrix matrix)
{
    this->rotationMatrix = matrix;
}





