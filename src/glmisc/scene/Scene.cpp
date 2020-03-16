//
// Created by shdwp on 3/14/2020.
//

#include "Scene.h"
#include "Camera.h"

#include "../objects/Light.h"

Scene::Scene() {
    uniform_buffer = make_unique<UniformBufferObject>(0, (vector<size_t>) {
        0, // projection mat4
        64, // world mat4
        128, // view position vec3
        144, // debug cursor pos vec3
        152, // debug opts int
        156, // lights count int
        160 + (0 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (1 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (2 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (3 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (4 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (5 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (6 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (7 * SHADER_LIGHT_STRUCT_SIZE),
        160 + (8 * SHADER_LIGHT_STRUCT_SIZE),
    });
}

void Scene::addLight(const shared_ptr<Light> &ptr) {
    this->lights->push_back(ptr);
}

void Scene::draw(const Camera &cam) {
    this->uniform_buffer->bind();

    this->uniform_buffer->set(0, cam.projection);
    this->uniform_buffer->set(1, cam.lookAt());
    this->uniform_buffer->set(2, cam.position);
    this->uniform_buffer->set(3, runtime_debug_focus);
    this->uniform_buffer->set(4, runtime_debug_flags);
    this->uniform_buffer->set(5, static_cast<uint32_t>(lights->size()));

    unsigned int i = 6;
    for (auto &light: *this->lights) {
        uint8_t lightStruct[SHADER_LIGHT_STRUCT_SIZE];
        light->shaderStruct(lightStruct);
        this->uniform_buffer->set(i++, lightStruct, SHADER_LIGHT_STRUCT_SIZE);
    }

    if (runtime_debug_flags & RuntimeDebugFlag_DisplayWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    this->skybox->tex_cubemap->bind();
    this->drawHierarchy(glm::mat4(1));
    this->skybox->render();
    this->uniform_buffer->unbind();
}

