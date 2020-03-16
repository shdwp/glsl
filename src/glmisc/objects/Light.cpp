//
// Created by shdwp on 3/13/2020.
//

#include "Light.h"

size_t Light::shaderStruct(uint8_t *buffer) {
    size_t offset = 0;
    memset(buffer, 0, SHADER_LIGHT_STRUCT_SIZE);

    auto _type = static_cast<uint32_t>(type);
    memcpy((buffer + offset), &_type, sizeof(_type));
    offset += 16;

    auto trans = transform();
    memcpy((buffer + offset), glm::value_ptr(trans), sizeof(glm::mat4));
    offset += sizeof(glm::mat4);

    memcpy((buffer + offset), glm::value_ptr(position), sizeof(glm::vec3));
    offset += sizeof(glm::vec4);

    memcpy((buffer + offset), glm::value_ptr(direction), sizeof(glm::vec3));
    offset += sizeof(glm::vec4);

    memcpy((buffer + offset), glm::value_ptr(ambient), sizeof(glm::vec3));
    offset += sizeof(glm::vec4);

    memcpy((buffer + offset), glm::value_ptr(diffuse), sizeof(glm::vec3));
    offset += sizeof(glm::vec4);

    memcpy((buffer + offset), glm::value_ptr(specular), sizeof(glm::vec3));
    offset += sizeof(glm::vec3);

    memcpy((buffer + offset), &constant, sizeof(float));
    offset += sizeof(float);

    memcpy((buffer + offset), &linear, sizeof(float));
    offset += sizeof(float);

    memcpy((buffer + offset), &quadratic, sizeof(float));
    offset += sizeof(float);

    float cutoff_cos = glm::cos(glm::radians(cutoff));
    memcpy((buffer + offset), &cutoff_cos, sizeof(float));
    offset += sizeof(float);

    assert(offset <= SHADER_LIGHT_STRUCT_SIZE);
    return offset;
}

void Light::setUniformColor(glm::vec3 color) {
    this->ambient = color * this->ambient;
    this->diffuse = color * this->diffuse;
    this->specular = color * this->specular;
}
