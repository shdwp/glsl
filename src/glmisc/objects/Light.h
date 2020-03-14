//
// Created by shdwp on 3/13/2020.
//

#ifndef GLPL_LIGHT_H
#define GLPL_LIGHT_H


#include "GObject.h"

class Light: public GObject {
public:
    glm::vec3 ambient_ = glm::vec3(0.25f);
    glm::vec3 diffuse_ = glm::vec3(0.5f);
    glm::vec3 specular_ = glm::vec3(1);

    float constant_ = 1.f;
    float linear_ = 0.09f;
    float quadratic_ = 0.032f;

    using GObject::GObject;
};

class Spotlight: public Light {
public:
    glm::vec3 direction_ = glm::vec3(0, 0, -1);
    float cutoff_ = glm::cos(glm::radians(12.f));

    using Light::Light;
};

#endif //GLPL_LIGHT_H
