#pragma once
#include <glad/gl.h>

class Window;
class Camera;

class Renderer{
public:
    void assignWindow(Window& window);
    void renderTriangle();
    void assignCamera(Camera* camera);

private:
    static bool _isInitialised;
    Camera* _camera;
};