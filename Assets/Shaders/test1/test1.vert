#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;

out vec3 vPosition;
out vec4 vColor;

uniform mat4 u_ViewProjection;

void main()
{
    vPosition = inPosition;
    vColor = inColor;
    gl_Position = u_ViewProjection * vec4(inPosition, 1.0);
}