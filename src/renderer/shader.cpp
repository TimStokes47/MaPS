#include "shader.h"
#include "core/logging.h"
#include <glad/gl.h>

Shader::Shader(std::string sourceCode, ShaderType shaderType)
{
    switch (shaderType){
        case ShaderType::VERTEX:
            _handle = glCreateShader(GL_VERTEX_SHADER);
            break;
        case ShaderType::FRAGMENT:
            _handle = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case ShaderType::GEOMETRY:
            _handle = glCreateShader(GL_GEOMETRY_SHADER);
            break;
    }

    const char* sourceCodeCString = sourceCode.c_str();
    glShaderSource(_handle, 1, &sourceCodeCString, nullptr);
    glCompileShader(_handle);

    int success;
    char infoLog[512];
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(_handle, 512, NULL, infoLog);
        LOG_ERROR("ERROR::SHADER::" << toString(shaderType) << "::COMPILATION_FAILED:\n" << infoLog);
    }
}

Shader::~Shader()
{
    glDeleteShader(_handle);
}

std::string toString(ShaderType shaderType)
{
    switch (shaderType){
        case ShaderType::VERTEX:
            return "VERTEX";
        case ShaderType::FRAGMENT:
            return "FRAGMENT";
        case ShaderType::GEOMETRY:
            return "GEOMETRY";
    }
    return "UNKNOWN TYPE";
}

ShaderProgram::ShaderProgram()
{
    _handle = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_handle);
}

void ShaderProgram::enable()
{
    glUseProgram(_handle);
}

void ShaderProgram::disable()
{
    glUseProgram(0);
}

void ShaderProgram::setUniform(const std::string &uniformName, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(_handle, uniformName.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::attachShader(const Shader &shader)
{
    glAttachShader(_handle, shader._handle);
}

void ShaderProgram::link()
{
    glLinkProgram(_handle);

    int success;
    char infoLog[512];
    glGetProgramiv(_handle, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(_handle, 512, NULL, infoLog);
        LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog);
    }
}
