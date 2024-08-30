#version 450

in vec2 v_TextureCoord;
in vec3 v_Normal;
in vec4 v_Color;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;

uniform float u_TilingFactor;

out vec4 fragColor;

void main()
{
    // 使用正确的 mix 函数来混合纹理颜色与顶点颜色
    vec4 texColor = mix(texture(u_Texture0, v_TextureCoord * u_TilingFactor), texture(u_Texture1, v_TextureCoord * u_TilingFactor), 1.0) * v_Color; // 获取纹理颜色
    fragColor = texColor; // 设置输出颜色
}