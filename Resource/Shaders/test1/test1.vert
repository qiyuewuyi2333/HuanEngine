#version 450

layout(location = 0) in vec3 inPosition;

out vec3 vPosition;

void main()
{
    vPosition = inPosition;
    gl_Position = vec4(inPosition, 1.0);
}