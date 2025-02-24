#include "window.h"
#include "core/logging.h"

#include "backends/imgui_impl_glfw.h"

Window::Window(int width, int height, const std::string &title)
{
    if (!_isGLFWInitialised){
        int initialisationSuccess = glfwInit();
        if (initialisationSuccess == GLFW_TRUE){
            LOG_DEBUG("GLFW initialised");
        } else {
            LOG_DEBUG("Failed to initialise GLFW");
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

void Window::enableImGui()
{
    ImGui_ImplGlfw_InitForOpenGL(_handle, true);   
}

bool Window::_isGLFWInitialised = false;