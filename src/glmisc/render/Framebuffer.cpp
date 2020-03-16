//
// Created by shdwp on 3/18/2020.
//

#include "Framebuffer.h"

Framebuffer::Framebuffer(uint32_t width, uint32_t height) {
    glGenFramebuffers(1, &gid);
    glBindFramebuffer(GL_FRAMEBUFFER, gid);

    color_tex = make_unique<Texture2D>(width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex->gid, 0);

    glGenRenderbuffers(1, &rid);
    glBindRenderbuffer(GL_RENDERBUFFER, rid);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rid);
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    shader_ = make_unique<ShaderProgram>((vector<shader_argument_struct>) {
            shader_argument(ShaderType_Vertex, std::string("../assets/shaders/fb_vert.glsl")),
            shader_argument(ShaderType_Fragment, std::string("../assets/shaders/fb_frag.glsl")),
    });

    auto vbo = VertexBufferObject(
            {
                    1, 1, 0, // top right
                    1, -1, 0, // bot right
                    -1, -1, 0, // bot left
                    -1, 1, 0, // top left
            },
            {
                    1, 1,
                    1, 0,
                    0, 0,
                    0, 1,
            },
            {},
            {
                    0, 1, 3,
                    1, 2, 3,
            });

    vbo_ = make_unique<VertexBufferObject>(move(vbo));
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, gid);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::render() {
    shader_->activate();
    shader_->uniform("offset", 1.f / 300);

    float kernel[9] = {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0,
    };

    auto kernel_mat = glm::make_mat3(kernel);
    shader_->uniform("kernel", kernel_mat);

    color_tex->bind();
    vbo_->bind();

    vbo_->draw();

    vbo_->unbind();
    color_tex->unbind();
    shader_->deactivate();
}
