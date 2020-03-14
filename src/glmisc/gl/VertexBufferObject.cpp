//
// Created by shdwp on 3/11/2020.
//

#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(float *data, size_t size) {
    glGenVertexArrays(1, &id_);
    glBindVertexArray(id_);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBufferObject::setIndices(size_t _count) {
    count = _count;
}

void VertexBufferObject::setIndices(size_t _count, uint32_t *data, size_t size) {
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    count = _count;
}

void VertexBufferObject::pushAttributePointer(unsigned int n, GLenum gl_type, size_t stride, size_t offset) {
    glVertexAttribPointer(attrib_idx, n, gl_type, GL_FALSE, stride, (void *)offset);
    glEnableVertexAttribArray(attrib_idx);

    attrib_idx++;
}

