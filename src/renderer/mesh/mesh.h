#pragma once
#include <glm/glm.hpp>
#include "renderer/buffers.h"

struct Mesh{
    VertexArray vertexArray;
    glm::mat4 modelTransform;
};