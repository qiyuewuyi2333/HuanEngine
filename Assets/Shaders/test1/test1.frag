#version 450

in vec3 vPosition;
in vec4 vColor;

out vec4 fragColor;

void main()
{
    fragColor = vColor;
}