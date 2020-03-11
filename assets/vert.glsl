#version 430 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec3 targetColor;
out vec2 textureCoord;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(pos, 1);

    textureCoord = texCoord;
    targetColor = vec3(0, 0, 0);

    float offset = (sin(time) + 1) / 2;
    if ((gl_VertexID % 2) == 0) {
        // gl_Position.x += offset / 20;
        targetColor.r += offset / 4;
    } else if ((gl_VertexID % 3) == 0) {
        // gl_Position.y += offset / 20;
        targetColor.g += offset / 4;
    }
}
