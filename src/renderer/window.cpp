#include "window.h"
#include <iostream>

Window::Window(int width, int height, const std::string &title)
{
    if (!_isGLFWInitialised){
        int initialisationSuccess = glfwInit();
        if (initialisationSuccess == GLFW_TRUE){
            std::cout << "GLFW initialised\n";
        } else {
            std::cout << "Failed to initialise GLFW\n";
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }
    
    _handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

Window::~Window()
{
    glfwDestroyWindow(_handle);
    glfwTerminate();
}

bool Window::isClosed()
{
    return glfwWindowShouldClose(_handle);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_handle);
}

void Window::enable()
{
    glfwMakeContextCurrent(_handle);
}

void Window::disable()
{
    glfwMakeContextCurrent(nullptr);
}

bool Window::_isGLFWInitialised = false;