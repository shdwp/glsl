#version 430 core

out vec4 FragColor;
in vec2 TexCoords;

uniform float offset;
uniform mat3 kernel;
uniform sampler2D tex;

void main() {
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right
    );

    vec3 samples[9];
    for (int i = 0; i < 9; i++) {
        samples[i] = vec3(texture(tex, TexCoords.xy + offsets[i]));
    }

    vec3 color = vec3(0);
    for (int i = 0; i < 9; i++) {
        int row = int(floor(i / 3));
        int col = i - (row * 3);
        color += samples[i] * kernel[row][col];
    }

    FragColor = vec4(color, 1);
}
