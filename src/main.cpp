#include <iostream>
#include "renderer/renderer.h"
#include "renderer/window.h"
#include "renderer/camera/orthographicCamera.h"
#include "renderer/mesh/mesh.h"
#include "renderer/buffers.h"

int main(int, char**){
    Window window(540, 540, "MaPS");
    Renderer renderer;
    renderer.assignWindow(window);

    OrthographicCamera camera(0.0f, 150.0f, 0.0f, 150.0f);
    renderer.assignCamera(&camera);

    std::vector<float> vertices = { 
        0.0, 0.0, 
        1.0f, 0.0f, 
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    std::vector<float> screenCorners = { 
        0.0, 0.0, 
        150.0f, 0.0f, 
        150.0f, 150.0f,
        0.0f, 150.0f
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3
    };

    std::vector<float> instanceOffsets;
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            instanceOffsets.push_back({1.5f * i});
            instanceOffsets.push_back({1.5f * j});
        }
    }

    VertexArray va;
    va.bind();

    VertexBuffer vb(screenCorners);
    vb.bind();
    vb.setDataFormat({{DataType::FLOAT, 2}});

    //VertexBuffer instances(instanceOffsets);
    //instances.bind();
    //instances.setDataFormat({{DataType::FLOAT, 2}}, 1, 1);

    IndexBuffer ib(indices);
    ib.bind();

    //va.unbind();

    Mesh mesh;
    mesh.vertexArray = va;
    mesh.modelTransform = glm::mat4(1.0f);
    mesh.numberOfIndices = indices.size();



    double lastTime = glfwGetTime();
    int nbFrames = 0;
    double timePerFrame = 0.0;

    while (!window.isClosed()){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.renderScreen(mesh);
        //renderer.renderMeshInstanced(mesh, 100 * 100);
        renderer.renderText(std::to_string(timePerFrame));
        window.swapBuffers();

        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            timePerFrame = 1000.0 / (double)nbFrames;
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
}
