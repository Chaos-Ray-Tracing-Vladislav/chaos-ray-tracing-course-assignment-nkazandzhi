#pragma once
#include "CRTMatrix.h"

class CRTCamera {
private:
    CRTVector position; // in 3D space
    CRTMatrix rotationMatrix; //each row holds the direction of the rotated unit vector of the camera local coordinate system

public:
    CRTCamera();
    CRTCamera(CRTVector position);

    //these change just the camera position, not its orientation
    //they have the same body function basically the change depends on the moveDir vector

    void truck(const CRTVector& moveDir); //moving the camera left or rigth ( x axis ) 
    void dolly(const CRTVector& moveDir); // moving the camera forward or backwards ( z axis )
    void pedestal(const CRTVector& moveDir); //move the camera up or down ( y axis )

    //these change the orientation
    void pan(const float degs); //rotate the camera horizontally to the left or to the right ( x axis )
    void tilt(const float degs); // rotate the camera vertically up to down or vice versa ( y axis )
    void roll(const float degs); // rotate the camera horizontally to the left or right around the z axis

    CRTVector get_position() const;
    CRTMatrix get_rotationMatrix() const;

};

//we also move the image plane along with the camera as we generate the new camera rays we take into account the new camera position