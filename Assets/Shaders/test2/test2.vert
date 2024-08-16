#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTextureCoord;

out vec3 vPosition;
out vec3 vColor;
out vec2 vTextureCoord;

uniform mat4 u_ViewProjection;

void main()
{
    vPosition = inPosition;
    vColor = inColor;
    vTextureCoord = inTextureCoord;
    gl_Position = u_ViewProjection * vec4(inPosition, 1.0);
}