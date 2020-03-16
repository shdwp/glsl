//
// Created by shdwp on 3/11/2020.
//

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "TextObject.h"

TextObject::TextObject(const shared_ptr<Texture2D> &tex) {
    shader_ = make_unique<ShaderProgram>((vector<shader_argument_t>){
        shader_argument(ShaderType_Vertex, "../assets/shaders/text_vert.glsl"),
        shader_argument(ShaderType_Fragment, "../assets/shaders/text_frag.glsl")
    });

    tex_ = tex;
}

void TextObject::setText(string str, float size) {
    auto rows = 16, cols = 16;
    auto char_width = 1.f / rows, char_height = 1.f / cols;

    auto vertices = make_unique<vector<float>>();
    auto texcoords = make_unique<vector<float>>();
    auto indices = make_unique<vector<uint32_t>>();

    for (uint32_t i = 0; i < str.length(); i++) {
        float ord = str.at(i);

        float col;
        modff(ord / cols, &col);
        float row = ord - col * cols;

        row = char_width * row;
        col = char_height * (cols - col - 1);

        float originX = ((float)i * size), originY = 0;
        float characterData[] = {
                originX + size, originY + size, 0, // top right
                originX + size, originY, 0, // bot right
                originX, originY, 0, // bot left
                originX, originY + size, 0, // top left
        };

        float texCoordsData[] = {
                row + char_width, col + char_height,  // top right
                row + char_width, col,  // bot right
                row, col,  // bot left
                row, col + char_height  // top left
        };

        auto offset = i * 4;
        uint32_t characterIndices[] = {
                offset, offset + 1, offset + 3,
                offset + 1, offset + 2, offset + 3,
        };

        vertices->insert(end(*vertices), characterData, characterData + 4 * 3);
        texcoords->insert(end(*texcoords), texCoordsData, texCoordsData + 4 * 2);
        indices->insert(end(*indices), characterIndices, characterIndices + 3 * 2);
    }

    vb_ = make_unique<VertexBufferObject>(*vertices, *texcoords, vector<float>(), *indices);
}

void TextObject::render(glm::mat4 proj) {
    if (vb_ != nullptr) {
        tex_->bind(GL_TEXTURE1);
        shader_->activate();
        shader_->uniform("tex", 1);
        shader_->uniform("trans", proj);

        vb_->bind();
        vb_->draw();
        vb_->unbind();
    }
}
