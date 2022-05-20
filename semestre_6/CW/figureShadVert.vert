#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec3 position;
in vec3 colors;
in vec3 normal;

out vec4 myColor;
out vec3 Normal;
out vec3 FragPos;

void main(void)
{
    myColor = vec4(colors, 1);
    Normal = normal;
    FragPos = vec3(model*vec4(position, 1.0));
    gl_Position = projection*view*model*vec4(position.xyz, 1);
}
