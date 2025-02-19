#include "renderer.h"
#include "window.h"
#include "shader.h"
#include "camera/camera.h"
#include "mesh/mesh.h"

#include "core/logging.h"
#include "core/fileUtilities.h"

#include <glm/gtc/matrix_transform.hpp>
#include <string>

void Renderer::assignWindow(Window& window)
{
    window.enable();

    if (!_isInitialised){
        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0){
            LOG_DEBUG("Failed to initialise OpenGL context");
            exit(-1);
        } else {
            LOG_DEBUG("Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version));
        }
        _isInitialised = true;
    }
}

void Renderer::renderMesh(const Mesh& mesh)
{
    std::string vertexShaderSource = readFileIntoString("../../resources/shaders/basic.vs");
    std::string fragmentShaderSource = readFileIntoString("../../resources/shaders/basic.fs");

    Shader vertexShader(vertexShaderSource, ShaderType::VERTEX);
    Shader fragmentShader(fragmentShaderSource, ShaderType::FRAGMENT);
    
    ShaderProgram shaderProgram;
    shaderProgram.attachShader(vertexShader);
    shaderProgram.attachShader(fragmentShader);
    shaderProgram.link();

    mesh.vertexArray.bind();
    shaderProgram.enable();
    shaderProgram.setUniform("u_projection", _camera->getProjectionMatrix());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    shaderProgram.disable();
    mesh.vertexArray.unbind();
}

void Renderer::assignCamera(Camera* camera)
{
    _camera = camera;
}

bool Renderer::_isInitialised = false;