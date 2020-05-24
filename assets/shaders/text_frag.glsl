#version 430

in vec2 TexPos;

out vec4 Color;

uniform sampler2D tex;

void main() {
    Color = texture(tex, TexPos);
}
