#version 430 core
#include scene_buffer.glsl

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNorm;

out vec2 TextureCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 local;
uniform mat4 textureMat;

void main() {
    vec4 local_Position = local * vec4(aPos, 1);
    gl_Position = projection * world * local_Position;

    TextureCoord = (textureMat * aTexCoord.xxyx).xz;
    Normal = mat3(transpose(inverse(local))) * aNorm;
    FragPos = local_Position.xyz;
}
