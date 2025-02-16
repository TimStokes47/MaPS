#include "renderer.h"
#include "window.h"

#include "core/logging.h"

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
}


bool Renderer::_isInitialised = false;