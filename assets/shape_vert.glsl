#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

out vec2 TextureCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 proj, world, local;

void main() {
    vec4 local_Position = local * vec4(aPos, 1);
    gl_Position = proj * world * local_Position;

    // TextureCoord = (local * vec4(aTexCoord.xy, 1, 1)).xy;
    TextureCoord = aTexCoord;
    Normal = mat3(transpose(inverse(local))) * aNorm;
    FragPos = local_Position.xyz;
}
