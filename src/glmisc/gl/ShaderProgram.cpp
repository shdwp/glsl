//
// Created by shdwp on 3/10/2020.
//

#include "ShaderProgram.h"
#include <istream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

shader_object_t load_shader(const char *path, GLenum type) {
    std::ifstream stream(path);
    assert(!(stream.rdstate() & std::ifstream::failbit));

    std::stringstream buf;
    buf << stream.rdbuf();

    std::string contents = buf.str();
    const char *contents_ptr = contents.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &contents_ptr, NULL);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Failed to compile shader " << path <<  ":\n" << infoLog << std::endl;
    }
    return shader;
}

shader_argument_t shader_argument(shader_argument_type type, std::string path) {
    shader_argument_struct value = {type, path};
    return value;
}

ShaderProgram::ShaderProgram(std::vector<shader_argument_t> shaders) {
    Id = glCreateProgram();

    for (shader_argument_t arg: shaders) {
        shader_object_t shader = 0;
        switch (arg.type) {
            case ShaderType_Vertex:
                shader = load_shader(arg.path.c_str(), GL_VERTEX_SHADER);
                break;

            case ShaderType_Fragment:
                shader = load_shader(arg.path.c_str(), GL_FRAGMENT_SHADER);
                break;
        }

        if (shader != 0) {
            glAttachShader(Id, shader);
        } else {
            std::cout << "failed to load shader" << std::endl;
        }
    }

    glLinkProgram(Id);

    int result; glGetProgramiv(Id, GL_LINK_STATUS, &result);
    if (!result) {
        char infoLog[512];
        glGetProgramInfoLog(Id, 512, nullptr, infoLog);
        std::cout << "Failed to link program:\n" << infoLog << std::endl;
    }
}

void ShaderProgram::uniform(const char *name, float a) {
    glUniform1f(glGetUniformLocation(Id, name), a);
}

void ShaderProgram::uniform(const char *name, int a) {
    glUniform1i(glGetUniformLocation(Id, name), a);
}

void ShaderProgram::uniform(const char *name, glm::vec3 vec) {
    glUniform3f(glGetUniformLocation(Id, name), vec.x, vec.y, vec.z);
}

void ShaderProgram::uniform(const char *name, glm::vec4 vec) {
    glUniform4f(glGetUniformLocation(Id, name), vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::uniform(const char *name, glm::mat4 mat) {
    glUniformMatrix4fv(glGetUniformLocation(Id, name), 1, GL_FALSE, glm::value_ptr(mat));
}
