//
// Created by shdwp on 3/14/2020.
//

#ifndef GLPL_SCENE_H
#define GLPL_SCENE_H


#include "../objects/GObject.h"

class Camera;

class Scene: public GObject {
public:

public:
    shared_ptr<Light> direction_light_;

    void draw(const Camera &cam);
};


#endif //GLPL_SCENE_H
