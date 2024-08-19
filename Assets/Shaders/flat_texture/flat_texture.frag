#version 450

in vec3 vPosition;
in vec2 vTextureCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

out vec4 fragColor;

void main()
{
    // ʹ����ȷ�� mix ���������������ɫ�붥����ɫ
    vec4 texColor = texture(u_Texture, vTextureCoord ) * u_Color; // ��ȡ������ɫ
    fragColor = texColor; // ���������ɫ
}