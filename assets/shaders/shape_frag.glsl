#version 430 core
#include scene_buffer.glsl

in vec2 TextureCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 Color;

uniform samplerCube skybox_tex;
uniform Material material;

vec4 calculate_light(Light light) {
    vec3 lightPos = (light.transform * vec4(light.pos, 1)).xyz;

    vec3 lightDir = normalize(lightPos - FragPos);
    float lightAngle = dot(lightDir, normalize(-light.dir));
    float lightDistance = length(lightPos - FragPos);

    if (light.type == 0) {
        lightDir = normalize(light.dir);
        lightDistance = 1;
        lightAngle = 1;
    } else if (light.type == 1) {
        lightAngle = 1;
    }

        /*
    #printf("\nlight type: %d\n", light.type);
    #printf("light trans: %^4g\n", light.transform[0]);
    #printf("light trans: %^4g\n", light.transform[1]);
    #printf("light trans: %^4g\n", light.transform[2]);
    #printf("light trans: %^4g\n", light.transform[3]);

    #printf("light pos: %^3g\n", lightPos);
    #printf("light dir: %^3g\n", light.dir);
    #printf("light ambient: %^3g, diffuse: %^3g, specular: %^3g\n", light.ambient, light.diffuse, light.specular);
    #printf("light constant: %g, linear: %g, quadratic: %g, cutoff: %g\n", light.constant, light.linear, light.quadratic, light.cutoff);
    #printf("light angle: %g, distance: %g\n", lightAngle, lightDistance);
    */

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
        vec3 viewDir = normalize(viewPosition - FragPos);
        vec3 reflectDir = reflect(-lightDir, Normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0), 32);
        if (isinf(spec)) {
            spec = 0.f;
        }
        specular = albedo * texture(material.tex_spec, TextureCoord) * spec * vec4(light.specular, 1);
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

    vec4 value = ambient + emission + (lightAngle > light.cutoff ? diffuse + specular: vec4(0));
    return value;
}

void main() {
    /*
    debugFocusSetup(gl_FragCoord.xy);
    #printf("viewpos: %^3g\n", viewPosition);
    #printf("lights total: %u\n", lightsCount);
    */

    for (int i = 0; i < lightsCount; i++) {
        Color += calculate_light(lights[i]);
    }

    vec3 direction = normalize(FragPos - viewPosition);
    vec3 reflection = reflect(direction, normalize(Normal));
    float angle = dot(normalize(reflection), normalize(Normal));
    float spec = texture(material.tex_spec, TextureCoord).x;
    vec3 reflected_color = texture(skybox_tex, reflection).xyz * spec;

    float dest = 1.f;
    if (angle < 0.2) {
        dest = 1.f;
    } else if (angle < 0.3) {
        dest = 1.f - (angle - 0.2) / 0.1;
    } else {
        dest = 0;
    }

    dest *= 0.2f;
    Color = Color * (1.f - dest);
    Color += vec4(reflected_color * dest, 1);
}
