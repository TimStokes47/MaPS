#pragma once
#include <glad/gl.h>

class Window;

class Renderer{
public:
    void assignWindow(Window& window);
    void renderTriangle();

private:
    static bool _isInitialised;
};