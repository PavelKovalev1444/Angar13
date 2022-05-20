#version 330 core

in vec3 position;
out vec4 myColor;
uniform mat4 matrixWave;
uniform float coeff;

void main(void)
{

    if(position.x >= -0.75f && position.x <= 0.75f && position.y >= -0.1f && position.y <= 0.1f){
        myColor =  vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }else if (position.x >= -0.1f && position.x <= 0.1f && position.y >= -0.75f && position.y <= 0.75f){
        myColor =  vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }else{
        myColor =  vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }
    gl_Position = vec4(position.x, position.y + 0.15*cos(position.x + coeff), position.z, 1);
}
