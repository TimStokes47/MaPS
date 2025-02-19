#include <iostream>
#include "renderer/renderer.h"
#include "renderer/window.h"
#include "renderer/camera/orthographicCamera.h"
#include "renderer/mesh/mesh.h"
#include "renderer/buffers.h"

int main(int, char**){
    Window window(960, 540, "MaPS");
    Renderer renderer;
    renderer.assignWindow(window);

    OrthographicCamera camera(0.0f, 5.0f, 0.0f, 3.0f);
    renderer.assignCamera(&camera);

    std::vector<float> vertices = { 
        0.0, 0.0, 
        1.0f, 0.0f, 
        1.0f, 1.0f
    };

    VertexArray va;
    va.bind();

    VertexBuffer vb(vertices);
    vb.bind();
    vb.setDataFormat({{DataType::FLOAT, 2}});

    Mesh triangle;
    triangle.vertexArray = va;
    triangle.modelTransform = glm::mat4(1.0f);

    while (!window.isClosed()){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.renderMesh(triangle);
        window.swapBuffers();
    }
}
