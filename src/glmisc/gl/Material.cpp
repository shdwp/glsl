//
// Created by shdwp on 3/13/2020.
//

#include "Material.h"

#include "../scene/Camera.h"
#include "../scene/Scene.h"
#include "../objects/Light.h"

Material::Material(unique_ptr<ShaderProgram> mShader, const shared_ptr<Texture2D> &_tex_albedo) {
    shader_ = move(mShader);
    tex_albedo_ = _tex_albedo;
}

Material Material::Base(const shared_ptr<Texture2D> &tex_albedo) {
    auto shader = make_unique<ShaderProgram>(vector<shader_argument_struct>(
            {
                    shader_argument(ShaderType_Vertex, std::string("../assets/shape_vert.glsl")),
                    shader_argument(ShaderType_Fragment, std::string("../assets/shape_frag.glsl")),
            }
    ));

    auto mat = Material(move(shader), tex_albedo);
    return mat;
}

Material Material::Base(glm::vec4 albedo) {
    auto shader = make_unique<ShaderProgram>(vector<shader_argument_struct>(
            {
                    shader_argument(ShaderType_Vertex, std::string("../assets/shape_vert.glsl")),
                    shader_argument(ShaderType_Fragment, std::string("../assets/shape_frag.glsl")),
            }
    ));

    auto mat = Material(move(shader), nullptr);
    mat.albedo = albedo;
    return mat;
}

Material Material::Light() {
    auto mat = Material::Base(glm::vec4(0));
    mat.emission = 1.f;
    return mat;
}

void Material::use(glm::mat4 local, const Scene &scene, const Camera &cam) {
    shader_->use();

    shader_->uniform("local", local);
    shader_->uniform("world", cam.lookAt());
    shader_->uniform("proj", cam.projection_);
    shader_->uniform("view", cam.position_);


    if (tex_albedo_) {
        tex_albedo_->bind(GL_TEXTURE0);
        shader_->uniform("material.has_albedo", true);
        shader_->uniform("material.tex_albedo", 0);
    }

    if (tex_spec_) {
        tex_spec_->bind(GL_TEXTURE1);
        shader_->uniform("material.has_spec", true);
        shader_->uniform("material.tex_spec", 1);
    }

    if (tex_emission_) {
        tex_emission_->bind(GL_TEXTURE2);
        shader_->uniform("material.has_emission", true);
        shader_->uniform("material.tex_emission", 2);
    }

    shader_->uniform("material.col_albedo", albedo);
    shader_->uniform("material.val_emission", emission);

    if (scene.direction_light_) {
        auto light = dynamic_cast<Spotlight *>(scene.direction_light_.get());

        shader_->uniform("light.pos", light->position_);
        shader_->uniform("light.dir", light->direction_);
        shader_->uniform("light.cutoff", glm::cos(glm::radians(light->cutoff_)));

        shader_->uniform("light.ambient", light->ambient_);
        shader_->uniform("light.diffuse", light->diffuse_);
        shader_->uniform("light.specular", light->specular_);

        shader_->uniform("light.constant", light->constant_);
        shader_->uniform("light.linear", light->linear_);
        shader_->uniform("light.quadratic", light->quadratic_);
    }
}
