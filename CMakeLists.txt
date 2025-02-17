cmake_minimum_required(VERSION 3.10.0)
project(MaPS VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(external/glfw)
add_subdirectory(external/glad/cmake)
find_package(OpenGL REQUIRED)

add_executable(MaPS src/main.cpp src/renderer/renderer.cpp src/renderer/window.cpp src/renderer/shader.cpp src/renderer/camera/camera.cpp src/renderer/camera/orthographicCamera.cpp src/core/fileUtilities.cpp)

glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6 EXTENSIONS GL_ARB_bindless_texture GL_EXT_texture_compression_s3tc)

target_include_directories(MaPS PRIVATE external/glfw/include gladsources/glad/include external/glm src)
target_link_libraries(MaPS glfw glad OpenGL::GL)

target_compile_definitions(MaPS PRIVATE
    $<$<CONFIG:Debug>:
        MAPS_DEBUG
    >
)