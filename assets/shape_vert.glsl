#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

out vec2 TextureCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 proj, world, local;

void main() {
    gl_Position = proj * world * local * vec4(aPos, 1);

    TextureCoord = aTexCoord;
    Normal = mat3(transpose(inverse(local))) * aNorm;
    FragPos = (local * vec4(aPos, 1)).xyz;
}
