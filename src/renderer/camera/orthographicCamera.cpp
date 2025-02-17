#include "orthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
{
    _projectionMatrix = glm::ortho(left, right, bottom, top);
}