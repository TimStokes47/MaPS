#pragma once
#include <string>

enum class ShaderType{
    VERTEX,
    FRAGMENT,
    GEOMETRY
};

class Shader{
public:
    Shader(std::string sourceCode, ShaderType shaderType);
    ~Shader();

private:
    unsigned int _handle;

friend class ShaderProgram;
};

class ShaderProgram{
public:
    ShaderProgram();
    ~ShaderProgram();

    void enable();
    void disable();

    void attachShader(const Shader& shader);
    void link();

private:
    unsigned int _handle;
};

std::string toString(ShaderType shaderType);