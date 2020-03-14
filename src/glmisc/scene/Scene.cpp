//
// Created by shdwp on 3/14/2020.
//

#include "Scene.h"

#include "Camera.h"

void Scene::draw(const Camera &cam) {
    this->drawHierarchy(glm::mat4(1), *this, cam);
}
