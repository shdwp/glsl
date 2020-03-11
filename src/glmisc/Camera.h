//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_CAMERA_H
#define GLPL_CAMERA_H

#include "gl_misc.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 direction;

    Camera(glm::vec3 _position, glm::vec3 _direction) {
        position = _position;
        direction = _direction;
    }

    glm::mat4 lookAt() {
        return glm::lookAt(
                this->position,
                this->position + this->direction,
                glm::vec3(0, 1, 0)
                );
    }
};


#endif //GLPL_CAMERA_H
