//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_VERTEXBUFFEROBJECT_H
#define GLPL_VERTEXBUFFEROBJECT_H

#include "../gl_misc.h"

class VertexBufferObject {
public:
    vertex_array_object_t Id = 0;

    VertexBufferObject(float *data, size_t size);

    void set_indices(size_t _count);

    void set_indices(size_t _count, unsigned int *data, size_t size);

    void push_attrib_pointer(
            unsigned int n,
            GLenum gl_type,
            size_t stride,
            size_t offset
            );

    void bind() {
        glBindVertexArray(Id);
    }

    void draw(GLenum mode = GL_TRIANGLES) {
        if (EBO) {
            glDrawElements(
                    mode,
                    count,
                    GL_UNSIGNED_INT,
                    0
            );
        } else {
            glDrawArrays(
                    mode,
                    0,
                    count);
        }
    }

    void bind_and_draw(GLenum mode = GL_TRIANGLES) {
        this->bind();
        this->draw(mode);
    }

private:
    unsigned int attrib_idx = 0;
    size_t count = 0;

    vertex_buffer_object_t VBO = 0;
    element_array_buffer_object_t EBO = 0;
};


#endif //GLPL_VERTEXBUFFEROBJECT_H
