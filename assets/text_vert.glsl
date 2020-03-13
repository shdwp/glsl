#version 430

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texPos;

out vec2 TexPos;

uniform mat4 trans;

void main() {
    gl_Position = trans * vec4(pos, 0, 1.f);

    TexPos = texPos;
}
