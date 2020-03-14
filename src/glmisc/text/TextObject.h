//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_TEXTOBJECT_H
#define GLPL_TEXTOBJECT_H

#include "../gl_misc.h"
#include "../gl/Texture2D.h"
#include "../gl/ShaderProgram.h"
#include "../gl/VertexBufferObject.h"

#include <glm/glm.hpp>

class TextObject {
    unique_ptr<VertexBufferObject> vb_;
    unique_ptr<ShaderProgram> shader_;
    shared_ptr<Texture2D> tex_;

public:
    glm::mat4 proj_ = glm::mat4(1.f);

    TextObject(const shared_ptr<Texture2D> &tex, string str, float size = 24.f);

    void render();
};

#endif //GLPL_TEXTOBJECT_H
