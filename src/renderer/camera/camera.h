#pragma once
#include <glm/glm.hpp>

class Camera{
public:
    const glm::mat4& getProjectionMatrix() const;

protected:
    glm::mat4 _projectionMatrix;
};