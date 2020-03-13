//
// Created by shdwp on 3/13/2020.
//

#include "TexturedShape.h"

TexturedShape::TexturedShape(const shared_ptr<Texture2D> &tex, float *buffer, size_t size) : Shape(buffer, size) {
    m_tex = tex;

    m_vbo->push_attrib_pointer(2, GL_FLOAT, sizeof(float) * 8, sizeof(float) * 3);
}

void TexturedShape::prepare_for(Camera *cam) {
    Shape::prepare_for(cam);

    m_tex->bind();
}
