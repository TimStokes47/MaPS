#include <iostream>
#include "renderer/renderer.h"
#include "renderer/window.h"
#include "renderer/camera/orthographicCamera.h"

int main(int, char**){
    Window window(960, 540, "MaPS");
    Renderer renderer;
    renderer.assignWindow(window);

    OrthographicCamera camera(0.0f, 5.0f, 0.0f, 3.0f);
    renderer.assignCamera(&camera);

    while (!window.isClosed()){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.renderTriangle();
        window.swapBuffers();
    }
}
