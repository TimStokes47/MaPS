#pragma once
#include <glfw/glfw3.h>
#include <string>

class Window{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool isClosed();

    void swapBuffers();
    void enable();
    void disable();

private:
    GLFWwindow* _handle;
    static bool _isGLFWInitialised;
};