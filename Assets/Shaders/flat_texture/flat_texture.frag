#version 450

in vec3 vPosition;
in vec2 vTextureCoord;

uniform sampler2D u_Texture;

out vec4 fragColor;

void main()
{
    // ʹ����ȷ�� mix ���������������ɫ�붥����ɫ
    vec4 texColor = texture(u_Texture, vTextureCoord.xy); // ��ȡ������ɫ
    fragColor = texColor; // ���������ɫ
}