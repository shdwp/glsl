//
// Created by shdwp on 3/19/2020.
//

#ifndef GLPL_TEXTURECUBEMAP_H
#define GLPL_TEXTURECUBEMAP_H

#include "../gl_misc.h"

class TextureCubemap {
public:
    texture_object_t gid;

    explicit TextureCubemap(const vector<string> &path, GLenum filter = GL_LINEAR);

    void bind() {
        glBindTexture(GL_TEXTURE_CUBE_MAP, gid);
    }

    void unbind() {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
};


#endif //GLPL_TEXTURECUBEMAP_H
