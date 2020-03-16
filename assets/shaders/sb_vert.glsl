#version 450
#include scene_buffer.glsl
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

void main() {
    TexCoords = aPos;

    mat4 trans = projection * mat4(mat3(world));
    vec4 pos = trans * vec4(aPos, 1);

    gl_Position = pos.xyww;
}
