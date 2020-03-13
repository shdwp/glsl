//
// Created by shdwp on 3/12/2020.
//

#ifndef GLPL_SHAPE_H
#define GLPL_SHAPE_H

#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../gl_misc.h"
#include "../gl/VertexBufferObject.h"
#include "../gl/Texture2D.h"
#include "../gl/ShaderProgram.h"
#include "../scene/Camera.h"

class PointLight;

class Shape {
protected:
    unique_ptr<VertexBufferObject> m_vbo;
    unique_ptr<ShaderProgram> m_shader;

public:
    glm::vec3 position = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);

    glm::vec4 albedo = glm::vec4(0);
    glm::vec3 ambientLight = glm::vec3(1.f);
    float emission = 0.f;

    Shape(float *buffer, size_t size);

    void affected_by(Shape *light);
    virtual void prepare_for(Camera *cam);

    void render();
};

#endif //GLPL_SHAPE_H
