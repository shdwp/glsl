//
// Created by shdwp on 3/12/2020.
//

#include "GObject.h"

GObject::GObject(Model &&model) {
    model_ = make_shared<Model>(move(model));
}

GObject::GObject(const shared_ptr<Model> &model) {
    model_ = model;
}

void GObject::drawHierarchy(const glm::mat4 parentLocal) {
    auto local = parentLocal;
    local = glm::translate(local, position);
    local = glm::scale(local, scale);
    local = local * glm::toMat4(rotation);

    if (model_) {
        model_->render(local);
    }

    for (auto &child: *children_) {
        child->drawHierarchy(local);
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

glm::mat4 GObject::transform() {
    glm::mat4 local = glm::mat4(1);
    if (this->parent_ != nullptr) {
        local = this->parent_->transform();
    }

    local = glm::translate(local, position);
    local = glm::scale(local, scale);
    local = local * glm::toMat4(rotation);

    return local;
}
