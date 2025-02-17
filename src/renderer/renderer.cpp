#include "renderer.h"
#include "window.h"
#include "shader.h"

#include "core/logging.h"
#include "core/fileUtilities.h"

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

void Renderer::renderTriangle()
{
    float vertices[] = { 
        0.0, 0.0, 
        1.0f, 0.0f, 
        1.0f, 1.0f
    };

    std::string vertexShaderSource = readFileIntoString("../../resources/shaders/basic.vs");
    std::string fragmentShaderSource = readFileIntoString("../../resources/shaders/basic.fs");

    Shader vertexShader(vertexShaderSource, ShaderType::VERTEX);
    Shader fragmentShader(fragmentShaderSource, ShaderType::FRAGMENT);
    
    ShaderProgram shaderProgram;
    shaderProgram.attachShader(vertexShader);
    shaderProgram.attachShader(fragmentShader);
    shaderProgram.link();

    unsigned int vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    shaderProgram.enable();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    shaderProgram.disable();
}

bool Renderer::_isInitialised = false;