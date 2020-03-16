//
// Created by shdwp on 3/11/2020.
//

#include "Texture2D.h"
#include <iostream>
#include "stb_image/stb_image.h"

Texture2D::Texture2D(uint32_t width, uint32_t height) {
    glGenTextures(1, &gid);
    glBindTexture(GL_TEXTURE_2D, gid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::Texture2D(string path, GLenum filter) {
    int w, h, ch;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &w, &h, &ch, 0);
    if (data == nullptr) {
        //s::critical("Failed to load texture {}", path);
        assert(false);
        return;
    }

    auto type = ch == 4 ? GL_RGBA : GL_RGB;

    glGenTextures(1, &gid);
    glBindTexture(GL_TEXTURE_2D, gid);
    glTexImage2D(GL_TEXTURE_2D, 0, type, w, h, 0, type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    stbi_image_free(data);
}
