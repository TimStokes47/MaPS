#include "renderer.h"
#include "window.h"

#include <iostream>

void Renderer::assignWindow(Window& window)
{
    window.enable();

    if (!_isInitialised){
        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0){
            std::cout << "Failed to initialise OpenGL context\n";
            exit(-1);
        } else {
            std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n";
        }
        _isInitialised = true;
    }
}


bool Renderer::_isInitialised = false;