#version 330 core

in vec3 position;
uniform mat4 projection;
uniform mat4 view;
in vec3 colors;
out vec4 myColor;

void main(void)
{
    myColor = vec4(colors, 1);
    gl_Position = projection*view*vec4(position.xyz, 1);
}
