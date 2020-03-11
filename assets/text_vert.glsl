#version 430

layout (location = 0) in vec2 pos;
layout (location = 1) in float ord;
layout (location = 1) in float corn;

out float Ord;
out float Corn;

void main() {
    gl_Position = vec4(pos, 0.f, 1.f);

    Ord = ord;
    Corn = corn;
}
