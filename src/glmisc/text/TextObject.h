//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_TEXTOBJECT_H
#define GLPL_TEXTOBJECT_H

#include "../gl_misc.h"
#include "../render/Texture2D.h"
#include "../render/ShaderProgram.h"
#include "../render/VertexBufferObject.h"

#include <glm/glm.hpp>

class TextObject {
    unique_ptr<VertexBufferObject> vb_ = nullptr;
    unique_ptr<ShaderProgram> shader_;
    shared_ptr<Texture2D> tex_;

public:
    TextObject(const shared_ptr<Texture2D> &tex);

    void render(glm::mat4 proj);

    void setText(string str, float size);
};

#endif //GLPL_TEXTOBJECT_H
