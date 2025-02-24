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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    const char* glsl_version = "#version 130";
    // Setup Platform/Renderer backends
    window.enableImGui();
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::string vertexShaderSource = readFileIntoString("../../resources/shaders/instancing.vs");
    std::string fragmentShaderSource = readFileIntoString("../../resources/shaders/basic.fs");

    Shader vertexShader(vertexShaderSource, ShaderType::VERTEX);
    Shader fragmentShader(fragmentShaderSource, ShaderType::FRAGMENT);
    
    _instancingShader = new ShaderProgram;
    _instancingShader->attachShader(vertexShader);
    _instancingShader->attachShader(fragmentShader);
    _instancingShader->link();


    vertexShaderSource = readFileIntoString("../../resources/shaders/signedDistance.vs");
    fragmentShaderSource = readFileIntoString("../../resources/shaders/signedDistance.fs");

    Shader vertexShader2(vertexShaderSource, ShaderType::VERTEX);
    Shader fragmentShader2(fragmentShaderSource, ShaderType::FRAGMENT);
    
    _signedDistanceShader = new ShaderProgram;
    _signedDistanceShader->attachShader(vertexShader2);
    _signedDistanceShader->attachShader(fragmentShader2);
    _signedDistanceShader->link();
}

void Renderer::renderMesh(const Mesh& mesh)
{
    mesh.vertexArray.bind();
    _instancingShader->enable();
    _instancingShader->setUniform("u_projection", _camera->getProjectionMatrix());
    glDrawElements(GL_TRIANGLES, mesh.numberOfIndices, GL_UNSIGNED_INT, nullptr);
    _instancingShader->disable();
    mesh.vertexArray.unbind();
}

void Renderer::renderMeshInstanced(const Mesh &mesh, unsigned int numberOfInstances)
{
    mesh.vertexArray.bind();
    _instancingShader->enable();
    _instancingShader->setUniform("u_projection", _camera->getProjectionMatrix());
    glDrawElementsInstanced(GL_TRIANGLES, mesh.numberOfIndices, GL_UNSIGNED_INT, nullptr, numberOfInstances);
    _instancingShader->disable();
    mesh.vertexArray.unbind();
}

void Renderer::assignCamera(Camera* camera)
{
    _camera = camera;
}

void Renderer::renderScreen(const Mesh& mesh)
{
    mesh.vertexArray.bind();
    _signedDistanceShader->enable();
    _signedDistanceShader->setUniform("u_projection", _camera->getProjectionMatrix());
    glDrawElements(GL_TRIANGLES, mesh.numberOfIndices, GL_UNSIGNED_INT, nullptr);
    _signedDistanceShader->disable();
    mesh.vertexArray.unbind();
}

void Renderer::renderText(const std::string &text)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Text(text.c_str());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Renderer::_isInitialised = false;