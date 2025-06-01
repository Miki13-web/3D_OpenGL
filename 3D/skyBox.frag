#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 lightColor;

void main()
{
    vec3 result = lightColor * texture(texture_diffuse1, TexCoords).rgb;
    FragColor = vec4(result, 1.0);
}