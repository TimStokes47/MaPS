#pragma once
#include <glad/gl.h>

class Window;
class Camera;
struct Mesh;

class Renderer{
public:
    void assignWindow(Window& window);
    void renderMesh(const Mesh& mesh);
    void assignCamera(Camera* camera);

private:
    static bool _isInitialised;
    Camera* _camera;
};