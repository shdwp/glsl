//
// Created by shdwp on 3/11/2020.
//

#ifndef GLPL_TEXTURE2D_H
#define GLPL_TEXTURE2D_H


#include <string>
#include "gl_misc.h"

class Texture2D {
public:
    texture_object_t Id;
    Texture2D(std::string path);

    void filter(GLenum val) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, val);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, val);
    }

    void bind(GLenum unit = GL_TEXTURE0) {
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_2D, Id);
    }
};


#endif //GLPL_TEXTURE2D_H
