#version 430 core

struct Material {
    bool has_albedo;
    sampler2D tex_albedo;

    bool has_diff;
    sampler2D tex_diff;

    bool has_spec;
    sampler2D tex_spec;

    bool has_emission;
    sampler2D tex_emission;

    vec4 col_albedo;
    float val_emission;
};

struct Light {
    vec3 pos;
    vec3 dir;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float cutoff;
};

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 Color;

uniform vec3 view;

uniform Material material;
uniform Light light;


void main() {
    vec3 lightDir = normalize(light.pos - FragPos);
    float lightAngle = dot(lightDir, normalize(-light.dir));
    float lightDistance = length(light.pos - FragPos);

    // albedo
    vec4 albedo;
    if (material.has_albedo) {
        albedo = texture(material.tex_albedo, TextureCoord);
    } else {
        albedo = material.col_albedo;
    }

    // ambient
    vec4 ambient =  albedo * vec4(light.ambient, 1);

    // diffuse
    float diff = max(dot(Normal, lightDir), 0);
    vec4 diffuse = texture(material.tex_albedo, TextureCoord) * diff * vec4(light.diffuse, 1);

    // specular
    vec4 specular = vec4(0);
    if (material.has_spec) {
        vec3 viewDir = normalize(view - FragPos);
        vec3 reflectDir = reflect(-lightDir, Normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
        if (isinf(spec)) {
            spec = 0.f;
        }
        specular = texture(material.tex_spec, TextureCoord) * spec * vec4(light.specular, 1);
    }

    // emission
    vec4 emission = vec4(0);
    if (material.has_emission) {
        emission = texture(material.tex_emission, TextureCoord);
    } else {
        emission = albedo * material.val_emission;
    }

    // attentuation
    float attentuation = 1.0 / (light.constant + light.linear * lightDistance + light.quadratic * pow(lightDistance, 2));
    ambient *= attentuation;
    diffuse *= attentuation;
    specular *= attentuation;

    if (lightAngle > light.cutoff) {
        Color = ambient + diffuse + specular + emission;
    } else {
        Color = ambient + emission;
    }
}
