#version 430 core
in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 Color;

uniform sampler2D tex;
uniform vec4 albedo;

uniform float emission;
uniform vec3 ambientLight;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 viewPosition;

void main() {
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(Normal, lightDir), 0);
    vec3 diffuse = diff * lightColor.xyz;

    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
    vec3 specular = 0.5f * spec * lightColor.xyz;

    vec4 color = texture(tex, TextureCoord) + albedo;
    //Color = (color) + (color * vec4(ambientLight + diffuse + specular, 1));
    //Color = vec4(vec3(1) + specular, 1);
    // Color = vec4(vec3(abs(specular.x), abs(specular.y), abs(specular.z)), 1);
    //Color = vec4(emission, emission, emission, 1);
}
