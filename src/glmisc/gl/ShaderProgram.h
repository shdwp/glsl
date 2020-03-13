//
// Created by shdwp on 3/10/2020.
//

#ifndef GLPL_SHADERPROGRAM_H
#define GLPL_SHADERPROGRAM_H

#include "../gl_misc.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>

enum shader_argument_type {
    ShaderType_Vertex,
    ShaderType_Fragment
};

struct shader_argument_struct {
    shader_argument_type type;
    std::string path;
};

typedef shader_argument_struct shader_argument_t;

shader_argument_t shader_argument(shader_argument_type type, std::string path);

class ShaderProgram {
public:
    program_object_t Id;

    ShaderProgram(std::vector<shader_argument_t> shaders);

    void use() {
        glUseProgram(Id);
    }

    void uniform(const char *name, int a);
    void uniform(const char *name, float a);

    void uniform(const char *name, glm::vec3 vec);
    void uniform(const char *name, glm::vec4 vec);
    void uniform(const char *name, glm::mat4 mat);
};


#endif //GLPL_SHADERPROGRAM_H
