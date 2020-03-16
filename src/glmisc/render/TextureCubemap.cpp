//
// Created by shdwp on 3/19/2020.
//

#include "TextureCubemap.h"
#include <iostream>
#include "stb_image/stb_image.h"

TextureCubemap::TextureCubemap(const vector<string> &facePaths, GLenum filter) {
    glGenTextures(1, &gid);
    glBindTexture(GL_TEXTURE_CUBE_MAP, gid);

    int w, h, ch;
    for (size_t i = 0; i < facePaths.size(); i++) {
        stbi_set_flip_vertically_on_load(false);
        uint8_t *data = stbi_load(facePaths[i].c_str(), &w, &h, &ch, 0);
        if (data == nullptr) {
            //s::critical("Failed to load cubemap texture face {} (i {})", facePaths[i], i);
            assert(false);
            return;
        }

        auto type = ch == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, type, w, h, 0, type, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE, 0);
}
