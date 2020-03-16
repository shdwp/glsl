//
// Created by shdwp on 3/19/2020.
//

#ifndef GLPL_SKYBOX_H
#define GLPL_SKYBOX_H


#include "../render/TextureCubemap.h"
#include "../render/VertexBufferObject.h"
#include "../render/ShaderProgram.h"

class Skybox {
    unique_ptr<ShaderProgram> shader_;
    unique_ptr<VertexBufferObject> vbo_;

public:
    shared_ptr<TextureCubemap> tex_cubemap;

    explicit Skybox(shared_ptr<TextureCubemap> tex);

    void render();
};


#endif //GLPL_SKYBOX_H
