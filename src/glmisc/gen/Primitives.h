//
// Created by shdwp on 3/12/2020.
//

#ifndef GLPL_PRIMITIVES_H
#define GLPL_PRIMITIVES_H


#include <cstdio>

class Primitives {
public:
    static unique_ptr<float[]> Cube(size_t *size);

    static unique_ptr<float[]> Plane(size_t *size);
};


#endif //GLPL_PRIMITIVES_H
