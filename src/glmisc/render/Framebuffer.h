//
// Created by shdwp on 3/18/2020.
//

#ifndef GLPL_FRAMEBUFFER_H
#define GLPL_FRAMEBUFFER_H

#include "../gl_misc.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "VertexBufferObject.h"

typedef GLuint framebuffer_object_t;
typedef GLuint render_buffer_object_t;

class Framebuffer {
    unique_ptr<ShaderProgram> shader_;
    unique_ptr<VertexBufferObject> vbo_;

public:
    framebuffer_object_t gid;
    render_buffer_object_t rid;
    unique_ptr<Texture2D> color_tex;

    Framebuffer(uint32_t width, uint32_t height);

    void bind();

    void unbind();

    void render();
};

#endif //GLPL_FRAMEBUFFER_H
