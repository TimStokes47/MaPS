#include <iostream>
#include "renderer/renderer.h"
#include "renderer/window.h"

int main(int, char**){
    Window window(960, 540, "MaPS");
    Renderer renderer;
    renderer.assignWindow(window);

    while (!window.isClosed()){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.renderTriangle();
        window.swapBuffers();
    }
}
