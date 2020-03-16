#version 450
#include scene_buffer.glsl

in vec3 TexCoords;
out vec4 FragColor;

uniform samplerCube tex;

void main() {
    FragColor = texture(tex, TexCoords);
}
