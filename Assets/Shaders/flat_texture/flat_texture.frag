#version 450

in vec3 vPosition;
in vec2 vTextureCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

out vec4 fragColor;

void main()
{
    // 使用正确的 mix 函数来混合纹理颜色与顶点颜色
    vec4 texColor = texture(u_Texture, vTextureCoord ) * u_Color; // 获取纹理颜色
    fragColor = texColor; // 设置输出颜色
}