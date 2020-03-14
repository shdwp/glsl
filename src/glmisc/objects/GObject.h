//
// Created by shdwp on 3/12/2020.
//

#ifndef GLPL_GOBJECT_H
#define GLPL_GOBJECT_H

#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../gl_misc.h"
#include "../gl/VertexBufferObject.h"
#include "../gl/Texture2D.h"
#include "../gl/ShaderProgram.h"
#include "../scene/Camera.h"
#include "../gl/Material.h"

class Light;
class GObject;
class Scene;

class GObject {
protected:
    unique_ptr<VertexBufferObject> vbo_;

    // assumes that parent will never be deallocated before child
    GObject *parent_ = nullptr;
    unique_ptr<vector<shared_ptr<GObject>>> children_ = make_unique<vector<shared_ptr<GObject>>>();

public:
    shared_ptr<Material> mat_;
    glm::vec3 position_ = glm::vec3(0);
    glm::vec3 scale_ = glm::vec3(1);

    explicit GObject(const shared_ptr<Material> &mat, float *buffer, size_t size);
    explicit GObject() = default;

    virtual void drawHierarchy(const glm::mat4 parentLocal, const Scene &scene, const Camera &cam);

    template<class T>
    shared_ptr<T> addChild(T &&child) {
        child.parent_= this;
        auto ptr = make_shared<T>(move(child));
        children_->push_back(ptr);
        return ptr;
    }

    void removeChild(GObject &child);
    void removeFromParent();
};

#endif //GLPL_GOBJECT_H
