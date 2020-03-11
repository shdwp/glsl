#version 430 core
in vec2 textureCoord;
in vec3 targetColor;

out vec4 Color;

uniform float time;
uniform sampler2D tex;

void main() {
    Color = texture(tex, textureCoord); // + vec4(targetColor, 1.f);
}
