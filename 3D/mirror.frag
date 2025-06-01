#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

out vec4 FragColor;

void main()
{
    // Lustro bêdzie mia³o jednolity kolor z lekkim odcieniem
    FragColor = vec4(0.1, 0.1, 0.1, 0.5);
}