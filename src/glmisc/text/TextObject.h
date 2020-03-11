//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_TEXTOBJECT_H
#define GLPL_TEXTOBJECT_H

#include "../gl_misc.h"
#include "../Texture2D.h"
#include "../ShaderProgram.h"
#include "../VertexBufferObject.h"

#include <glm/glm.hpp>

class TextObject {
    VertexBufferObject *m_vb;
    ShaderProgram *m_shader;
    std::string m_str;

public:
    TextObject(Texture2D *tex, std::string *str);

    void render(glm::mat4 trans);
};

#endif //GLPL_TEXTOBJECT_H
