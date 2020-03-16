//
// Created by shdwp on 3/14/2020.
//

#ifndef GLPL_SCENE_H
#define GLPL_SCENE_H


#include "../objects/GObject.h"
#include "../render/UniformBufferObject.h"
#include "../util/runtime_debug.h"
#include "../objects/Skybox.h"

class Camera;

class Scene: public GObject {
public:
    unique_ptr<UniformBufferObject> uniform_buffer;
    unique_ptr<vector<shared_ptr<Light>>> lights = make_unique<vector<shared_ptr<Light>>>();
    shared_ptr<Skybox> skybox;

    runtime_debug_type_t runtime_debug_flags = 0;
    glm::vec2 runtime_debug_focus = glm::vec2(0);

    Scene();

    void addLight(const shared_ptr<Light> &ptr);

    void draw(const Camera &cam);
};


#endif //GLPL_SCENE_H
