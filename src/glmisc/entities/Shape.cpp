//
// Created by shdwp on 3/12/2020.
//

#include "Shape.h"

Shape::Shape(float *buffer, size_t size) {
    m_vbo = make_unique<VertexBufferObject>(buffer, size);
    m_vbo->set_indices(size / (sizeof(float) * 8));
    m_vbo->push_attrib_pointer(3, GL_FLOAT, sizeof(float) * 8, 0);
    m_vbo->push_attrib_pointer(3, GL_FLOAT, sizeof(float) * 8, sizeof(float) * 5);

    m_shader = make_unique<ShaderProgram>((vector<shader_argument_t>){
        shader_argument(ShaderType_Vertex, std::string("../assets/shape_vert.glsl")),
        shader_argument(ShaderType_Fragment, std::string("../assets/shape_frag.glsl")),
    });
}

void Shape::render() {
    m_vbo->bind_and_draw();
}

void Shape::prepare_for(Camera *cam) {
    auto local = glm::mat4(1);
    local = glm::translate(local, position);
    local = glm::scale(local, scale);

    m_shader->use();
    m_shader->uniform("local", local);
    m_shader->uniform("world", cam->lookAt());
    m_shader->uniform("proj", cam->projection);
    m_shader->uniform("viewPosition", cam->position);

    m_shader->uniform("albedo", albedo);
    m_shader->uniform("emission", emission);
    m_shader->uniform("ambientLight", ambientLight);
}

void Shape::affected_by(Shape *light) {
    m_shader->uniform("lightPosition", light->position);
    m_shader->uniform("lightColor", light->albedo);
}
