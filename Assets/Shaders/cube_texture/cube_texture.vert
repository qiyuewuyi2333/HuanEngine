#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTextureCoord;

out vec2 vTextureCoord;


uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    vTextureCoord = inTextureCoord;
    gl_Position = u_ViewProjection * u_Transform * vec4(inPosition, 1.0);
}