//
// Created by shdwp on 3/12/2020.
//

#ifndef GLPL_GOBJECT_H
#define GLPL_GOBJECT_H

#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../gl_misc.h"
#include "../scene/Camera.h"
#include "../render/VertexBufferObject.h"
#include "../render/Texture2D.h"
#include "../render/ShaderProgram.h"
#include "../render/Material.h"
#include "../render/Model.h"

class GObject;

class GObject {
protected:
    shared_ptr<Model> model_ = nullptr;

    // assumes that parent will never be deallocated before child
    GObject *parent_ = nullptr;
    unique_ptr<vector<shared_ptr<GObject>>> children_ = make_unique<vector<shared_ptr<GObject>>>();

public:
    glm::vec3 position = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);
    glm::quat rotation = glm::quat(0, 0, 0, 0);

    explicit GObject() = default;
    explicit GObject(const shared_ptr<Model> &model);
    explicit GObject(Model &&model);

    virtual void drawHierarchy(const glm::mat4 parentLocal);

    glm::mat4 transform();

    template<class T>
    shared_ptr<T> addChild(T &&child) {
        child.parent_= this;
        auto ptr = make_shared<T>(move(child));
        children_->emplace_back(ptr);
        return ptr;
    }

    template<class T>
    void addChild(shared_ptr<T> child) {
        child->parent_= this;
        children_->emplace_back(child);
    }

    void removeChild(GObject &child);
    void removeFromParent();
};

#endif //GLPL_GOBJECT_H
