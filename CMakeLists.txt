cmake_minimum_required(VERSION 3.10.0)
project(MaPS VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MaPS main.cpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glew/build/cmake)
find_package(OpenGL REQUIRED)

target_include_directories(MaPS PUBLIC external/glfw/include external/glew/include)
target_link_libraries(MaPS glfw glew_s OpenGL::GL)
