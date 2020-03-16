//
// Created by shdwp on 3/16/2020.
//

#ifndef GLPL_STORE_H
#define GLPL_STORE_H


#include "../render/Material.h"
#include "../render/Texture2D.h"
#include "../render/Model.h"

class Store {
public:
    shared_ptr<Model> LoadModel(string base_path, string name);

    static Store& instance();
};


#endif //GLPL_STORE_H
