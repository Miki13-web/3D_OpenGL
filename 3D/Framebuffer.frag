#version 330 core
out vec4 FragColor;
in vec2 texCoords;
uniform sampler2D screenTexture;

const float offset = 1.0 / 800.0;

vec2 offsets[9] = vec2[](
    vec2(-offset,  offset), vec2( 0.0f,  offset), vec2( offset,  offset),
    vec2(-offset,  0.0f),   vec2( 0.0f,  0.0f),   vec2( offset,  0.0f),
    vec2(-offset, -offset), vec2( 0.0f, -offset), vec2( offset, -offset)
);

float kernel[9] = float[](
    1.0 / 16, 2.0 / 16, 1.0 / 16,
    2.0 / 16, 4.0 / 16, 2.0 / 16,
    1.0 / 16, 2.0 / 16, 1.0 / 16
);

void main()
{
    vec3 color = vec3(0.0);
    for(int i = 0; i < 9; ++i)
        color += texture(screenTexture, texCoords + offsets[i]).rgb * kernel[i];
    FragColor = vec4(color, 1.0);
}
