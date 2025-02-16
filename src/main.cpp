#include <iostream>
#include "renderer/renderer.h"
#include "renderer/window.h"

int main(int, char**){
    Window window(960, 540, "MaPS");
    Renderer renderer;
    renderer.assignWindow(window);

    while (!window.isClosed()){
        glfwPollEvents();
        window.swapBuffers();
    }
}
