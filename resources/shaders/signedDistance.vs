#version 330 core
layout (location = 0) in vec2 aPos;
uniform mat4 u_projection;
out vec2 position;

void main()
{
   position = aPos;
   gl_Position = u_projection * vec4(aPos, 0.0, 1.0);
}