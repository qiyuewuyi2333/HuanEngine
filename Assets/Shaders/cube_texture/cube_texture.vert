#version 450

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TextureCoord;
layout(location = 3) in vec4 in_Color;

out vec2 v_TextureCoord;
out vec3 v_Normal;
out vec4 v_Color;

uniform mat4 u_ProjectionView;

void main()
{
    v_TextureCoord = in_TextureCoord;
    v_Normal = in_Normal;
    v_Color = in_Color;
    gl_Position = u_ProjectionView * vec4(in_Position, 1.0);
}