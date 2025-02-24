#pragma once
#include <glad/gl.h>
#include <string>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "shader.h"

class Window;
class Camera;
struct Mesh;

class Renderer{
public:
    void assignWindow(Window& window);
    void renderMesh(const Mesh& mesh);
    void renderMeshInstanced(const Mesh& mesh, unsigned int numberOfInstances);
    void assignCamera(Camera* camera);
    void renderScreen(const Mesh& mesh);
    void renderText(const std::string& text);

private:
    static bool _isInitialised;
    Camera* _camera;
    ShaderProgram* _instancingShader;
    ShaderProgram* _signedDistanceShader;
};