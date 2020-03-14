//
// Created by shdwp on 3/12/2020.
//

#include "GObject.h"
#include "../scene/Scene.h"

GObject::GObject(const shared_ptr<Material> &mat, float *buffer, size_t size) {
    vbo_ = make_unique<VertexBufferObject>(buffer, size);
    vbo_->setIndices(size / (sizeof(float) * 8));
    vbo_->pushAttributePointer(3, GL_FLOAT, sizeof(float) * 8, 0);
    vbo_->pushAttributePointer(3, GL_FLOAT, sizeof(float) * 8, sizeof(float) * 5);
    vbo_->pushAttributePointer(2, GL_FLOAT, sizeof(float) * 8, sizeof(float) * 3);

    mat_ = mat;
}

void GObject::drawHierarchy(const glm::mat4 parentLocal, const Scene &scene, const Camera &cam) {
    auto local = parentLocal;
    local = glm::translate(local, position_);
    local = glm::scale(local, scale_);

    if (vbo_) {
        mat_->use(local, scene, cam);
        vbo_->bindAndDraw();
    }

    for (auto &child: *children_) {
        child->drawHierarchy(local, scene, cam);
    }
}

void GObject::removeChild(GObject &child) {
}


void GObject::removeFromParent() {
    if (parent_ != nullptr) {
        parent_->removeChild(*this);
        parent_ = nullptr;
    }
}

