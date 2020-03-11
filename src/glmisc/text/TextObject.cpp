//
// Created by shdwp on 3/11/2020.
//

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TextObject.h"

TextObject::TextObject(Texture2D *tex, std::string *str) {
    auto data_stride = 4 * 4;
    auto data_size = str->length() * sizeof(float) * data_stride;
    auto data = (float *)malloc(data_size);

    auto indices_stride = 6;
    auto indices_size = str->length() * indices_stride * sizeof(uint32_t);
    auto indices = (uint32_t *)malloc(indices_size);

    for (uint32_t i = 0; i < str->length(); i++) {
        float ord = str->at(i);
        float originX = (float)i, originY = 0;
        float w = 1, h = 1;

        float verts[] = {
                originX, originY, ord, 0,  // bot left
                originX + w, originY, ord, 1,  // bot right
                originX + w, originY + h, ord, 2,  // top right
                originX, originY + h, ord, 3  // top left
        };

        uint32_t inds[] = {
                i * data_stride, i * data_stride + 1, i * data_stride + 3,
                i * data_stride, i * data_stride + 2, i * data_stride + 3
        };

        memcpy(data + i * data_stride, verts, sizeof(float) * data_stride);
        memcpy(indices + i * indices_stride, inds, sizeof(uint32_t ) * indices_stride);
        break;
    }

    float vts[] = {
            0, 0, 97, 0,
            0, 1, 97, 1,
            1, 1, 97, 2,
            // 0, 1, 97, 3,
    };

    /*
    for (auto i = 0; i < 1 * data_stride; i++) {
        std::cout << data[i] << std::endl;
    }
     */

    //m_vb = new VertexBufferObject(data, data_size);
    //m_vb->set_indices(indices_size / sizeof(uint32_t), indices, indices_size);
    m_vb = new VertexBufferObject(vts, sizeof(vts));
    m_vb->set_indices(3);
    m_vb->push_attrib_pointer(2, GL_FLOAT, sizeof(float) * data_stride, 0);
    m_vb->push_attrib_pointer(1, GL_FLOAT, sizeof(float) * data_stride, sizeof(float) * data_stride + 2);
    m_vb->push_attrib_pointer(1, GL_FLOAT, sizeof(float) * data_stride, sizeof(float) * data_stride + 3);

    m_shader = new ShaderProgram({
        shader_argument(ShaderType_Vertex, "../assets/text_vert.glsl"),
        shader_argument(ShaderType_Fragment, "../assets/text_frag.glsl")
    });

    free(data);
    free(indices);
}

void TextObject::render(glm::mat4 trans) {
    m_shader->use();
    m_shader->uniform_matrix("trans", glm::value_ptr(trans));

    m_vb->bind_and_draw();
}
