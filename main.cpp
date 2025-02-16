#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main(int, char**){
    int initialisationSuccess = glfwInit();
    if (initialisationSuccess == GLFW_TRUE){
        std::cout << "GLFW initialised\n";
    } else {
        std::cout << "Failed to initialise GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(960, 540, "MaPS", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0){
        std::cout << "Failed to initialise OpenGL context\n";
        return -1;
    } else {
        std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << "\n";
    }

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
