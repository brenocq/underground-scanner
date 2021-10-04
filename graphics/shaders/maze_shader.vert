#version 330 core
layout (location = 0) in vec3 inPos;

uniform mat4 model;
uniform mat4 viewProjection;
uniform vec4 color;

out vec4 fragColor;

void main()
{
    gl_Position = viewProjection * model * vec4(inPos, 1.0); 
    fragColor = vec4(1,0,0,1);
}  
