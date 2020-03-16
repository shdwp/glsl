//
// Created by shdwp on 3/13/2020.
//

#ifndef GLPL_LIGHT_H
#define GLPL_LIGHT_H


#include "GObject.h"

#define SHADER_LIGHT_STRUCT_SIZE 176

enum LightType {
    LightType_Directional,
    LightType_Point,
    LightType_Spotlight,
};

class Light: public GObject {
public:
    LightType type = LightType_Directional;
    glm::vec3 direction = glm::vec3(0, 0, -1);

    glm::vec3 ambient = glm::vec3(0.25f);
    glm::vec3 diffuse = glm::vec3(1.f);
    glm::vec3 specular = glm::vec3(1);

    float constant = 1.f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    float cutoff = 40.f;

    using GObject::GObject;

    size_t shaderStruct(uint8_t *buffer);
    void setUniformColor(glm::vec3 color);
};

#endif //GLPL_LIGHT_H
