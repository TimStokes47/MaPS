cmake_minimum_required(VERSION 3.10.0)
project(MaPS VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MaPS main.cpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glad/cmake)
find_package(OpenGL REQUIRED)

glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6 EXTENSIONS GL_ARB_bindless_texture GL_EXT_texture_compression_s3tc)

target_include_directories(MaPS PUBLIC external/glfw/include gladsources/glad/include)
target_link_libraries(MaPS glfw glad OpenGL::GL)
