#version 450

in vec3 vPosition;
in vec2 vTextureCoord;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

uniform vec4 u_Color;
uniform float u_TilingFactor;

out vec4 fragColor;

void main()
{
    // 使用正确的 mix 函数来混合纹理颜色与顶点颜色
    vec4 texColor = mix(texture(u_Texture0, vTextureCoord * u_TilingFactor), texture(u_Texture1, vTextureCoord * u_TilingFactor), 1.0) * u_Color; // 获取纹理颜色
    fragColor = texColor; // 设置输出颜色
}