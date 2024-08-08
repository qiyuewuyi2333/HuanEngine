#version 450

in vec3 vPosition;

out vec4 fragColor;

void main()
{
    fragColor = vec4(vPosition + 0.5, 1.0);
}