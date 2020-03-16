struct Material {
    bool has_albedo;
    sampler2D tex_albedo;

    bool has_diff;
    sampler2D tex_diff;

    bool has_spec;
    sampler2D tex_spec;

    bool has_emission;
    sampler2D tex_emission;

    bool has_sheen;
    sampler2D tex_sheen;

    vec4 col_albedo;
    float val_emission;
};

struct Light {
    int type; // 0
    mat4 transform; // 32

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

layout (std140, binding = 0) uniform Scene {
    mat4 projection; // 0
    mat4 world; // 64

    vec3 viewPosition; // 128

    vec2 debugFocusPos; // 144
    int debugOpts; // 152

    int lightsCount; // 156
    Light lights[8]; // 160
}; // 1040

void debugFocusSetup(vec2 coords) {
    if ((debugOpts & (1 >> 0)) >= 1 && floor(debugFocusPos) == floor(coords)) {
        enablePrintf();
        #printf(":: DEBUG @%^2g\n", coords);
    }
}