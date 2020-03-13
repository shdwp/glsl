//
// Created by shdwp on 3/11/2020.
//

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TextObject.h"

TextObject::TextObject(shared_ptr<Texture2D> tex, string str, float size) {
    auto data_el_count = 4;
    auto data_stride = 4 * data_el_count;
    auto data_size = str.length() * sizeof(float) * data_stride;
    auto data = (float *)malloc(data_size);

    auto indices_stride = 6;
    auto indices_size = str.length() * indices_stride * sizeof(uint32_t);
    auto indices = (uint32_t *)malloc(indices_size);

    auto rows = 16, cols = 16;
    auto char_width = 1.f / rows, char_height = 1.f / cols;

    for (uint32_t i = 0; i < str.length(); i++) {
        float ord = str.at(i);

        float col;
        modff(ord / cols, &col);
        float row = ord - col * cols;

        row = char_width * row;
        col = char_height * (cols - col - 1);

        float originX = (float)i * size, originY = 0;
        float characterData[] = {
                originX + size, originY + size, row + char_width, col + char_height,  // top right
                originX + size, originY, row + char_width, col,  // bot right
                originX, originY, row, col,  // bot left
                originX, originY + size, row, col + char_height  // top left
        };
        /*
        float characterData[] = {
                originX + size, originY + size, 1, 1,  // top right
                originX + size, originY, 1, 0,  // bot right
                originX, originY, 0, 0,  // bot left
                originX, originY + size, 0, 1 // top left
        };
         */

        auto offset = i * data_el_count;
        uint32_t characterIndices[] = {
                offset, offset + 1, offset + 3,
                offset + 1, offset + 2, offset + 3,
        };

        memcpy(data + i * data_stride, characterData, sizeof(float) * data_stride);
        memcpy(indices + i * indices_stride, characterIndices, sizeof(uint32_t ) * indices_stride);
    }

    /*
    for (auto i = 0; i < 2 * data_stride; i++) {
        std::cout << data[i] << std::endl;
    }
     */

    m_vb = make_unique<VertexBufferObject>(data, data_size);
    m_vb->set_indices(indices_size / sizeof(uint32_t), indices, indices_size);
    m_vb->push_attrib_pointer(2, GL_FLOAT, sizeof(float) * data_el_count, 0);
    m_vb->push_attrib_pointer(2, GL_FLOAT, sizeof(float) * data_el_count, sizeof(float) * 2);

    m_shader = make_unique<ShaderProgram>((vector<shader_argument_t>){
        shader_argument(ShaderType_Vertex, "../assets/text_vert.glsl"),
        shader_argument(ShaderType_Fragment, "../assets/text_frag.glsl")
    });

    m_tex = tex;

    free(data);
    free(indices);
}

void TextObject::render() {
    m_tex->bind();

    m_shader->use();
    m_shader->uniform("trans", proj);

    m_vb->bind_and_draw(GL_TRIANGLES);
}
