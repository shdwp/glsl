//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_TEXTURE2D_H
#define GLPL_TEXTURE2D_H


#include <string>
#include "../gl_misc.h"

class Texture2D {
public:
    texture_object_t id_;
    Texture2D(string path, GLenum filter = GL_NEAREST);

    void bind(GLenum unit = GL_TEXTURE0) {
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D, id_);
    }

    static void Unbind(GLenum unit = GL_TEXTURE0) {
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};


#endif //GLPL_TEXTURE2D_H
