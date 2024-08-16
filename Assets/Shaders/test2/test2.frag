#version 450

in vec3 vPosition;
in vec3 vColor;
in vec2 vTextureCoord;

uniform sampler2D u_Texture;

out vec4 fragColor;

void main()
{
    // 使用正确的 mix 函数来混合纹理颜色与顶点颜色
    vec3 texColor = texture(u_Texture, vTextureCoord.xy).rgb; // 获取纹理颜色
    vec3 mixedColor = mix(texColor, vColor, 0.5); // 混合颜色
    fragColor = vec4(mixedColor, 1.0); // 设置输出颜色
}