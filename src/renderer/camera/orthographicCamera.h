#pragma once
#include "camera.h"

class OrthographicCamera : public Camera{
public:
    OrthographicCamera(float left, float right, float bottom, float top);
};