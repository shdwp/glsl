//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_CAMERA_H
#define GLPL_CAMERA_H

#include "../gl_misc.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::mat4 projection_;
    glm::vec3 position_;
    glm::vec3 direction_;

    Camera(glm::mat4 projection, glm::vec3 position, glm::vec3 direction): projection_(projection), position_(position), direction_(direction) { }

    glm::mat4 lookAt() const {
        return glm::lookAt(position_, position_ + direction_, glm::vec3(0, 1, 0));
    }
};


#endif //GLPL_CAMERA_H
