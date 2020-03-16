//
// Created by shdwp on 3/16/2020.
//

#ifndef GLPL_MODEL_H
#define GLPL_MODEL_H


#include "../gl_misc.h"
#include "VertexBufferObject.h"
#include "Material.h"

class Model {
public:
    unique_ptr<vector<string>> identifiers;
    unique_ptr<vector<VertexBufferObject>> buffers;
    unique_ptr<vector<shared_ptr<Material>>> materials;

    Model(vector<VertexBufferObject> buffers, vector<shared_ptr<Material>> materials, const vector<string> *_identifiers = nullptr);

    static Model Load(const string &base_path, const string &obj_name, const shared_ptr<Material> &override_mat = nullptr);

    void render(const glm::mat4 &local);
};


#endif //GLPL_MODEL_H
