#include "camera.h"

const glm::mat4 &Camera::getProjectionMatrix() const
{
    return _projectionMatrix;
}