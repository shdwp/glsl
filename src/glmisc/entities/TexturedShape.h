//
// Created by shdwp on 3/13/2020.
//

#ifndef GLPL_TEXTUREDSHAPE_H
#define GLPL_TEXTUREDSHAPE_H

#include "Shape.h"

class TexturedShape: public Shape {
    shared_ptr<Texture2D> m_tex;

public:
    TexturedShape(const shared_ptr<Texture2D> &tex, float *buffer, size_t size);

    void prepare_for(Camera *cam) override;
};


#endif //GLPL_TEXTUREDSHAPE_H
