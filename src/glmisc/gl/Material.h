//
// Created by shdwp on 3/13/2020.
//

#ifndef GLPL_MATERIAL_H
#define GLPL_MATERIAL_H


#include "ShaderProgram.h"
#include "Texture2D.h"

class Light;
class Scene;
class Camera;

class Material {
    unique_ptr<ShaderProgram> shader_;

public:
    shared_ptr<Texture2D> tex_albedo_;
    shared_ptr<Texture2D> tex_emission_;
    shared_ptr<Texture2D> tex_spec_;

    glm::vec4 albedo = glm::vec4(0);
    float emission = 0.f;

    explicit Material(unique_ptr<ShaderProgram> mShader, const shared_ptr<Texture2D> &m_albedo);

    static Material Base(const shared_ptr<Texture2D> &m_albedo);
    static Material Base(glm::vec4 albedo);
    static Material Light();

    void use(glm::mat4 local, const Scene &scene, const Camera &cam);
};


#endif //GLPL_MATERIAL_H
