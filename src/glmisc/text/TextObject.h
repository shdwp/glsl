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
    unique_ptr<VertexBufferObject> m_vb;
    unique_ptr<ShaderProgram> m_shader;
    shared_ptr<Texture2D> m_tex;

public:
    glm::mat4 proj = glm::mat4(1.f);

    TextObject(shared_ptr<Texture2D> tex, string str, float size = 24.f);

    void render();
};

#endif //GLPL_TEXTOBJECT_H
