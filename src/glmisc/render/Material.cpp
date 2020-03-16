//
// Created by shdwp on 3/13/2020.
//

#include "Material.h"

#include "../scene/Camera.h"
#include "../scene/Scene.h"
#include "../objects/Light.h"

Material::Material(unique_ptr<ShaderProgram> mShader, const shared_ptr<Texture2D> &_tex_albedo) {
    shader_ = move(mShader);
    tex_albedo = _tex_albedo;
}

Material Material::Base(const shared_ptr<Texture2D> &tex_albedo) {
    auto shader = make_unique<ShaderProgram>(vector<shader_argument_struct>(
            {
                    shader_argument(ShaderType_Vertex, std::string("../assets/shaders/shape_vert.glsl")),
                    shader_argument(ShaderType_Fragment, std::string("../assets/shaders/shape_frag.glsl")),
            }
    ));

    auto mat = Material(move(shader), tex_albedo);
    return mat;
}

Material Material::Base(glm::vec4 albedo) {
    auto shader = make_unique<ShaderProgram>(vector<shader_argument_struct>(
            {
                    shader_argument(ShaderType_Vertex, std::string("../assets/shaders/shape_vert.glsl")),
                    shader_argument(ShaderType_Fragment, std::string("../assets/shaders/shape_frag.glsl")),
            }
    ));

    auto mat = Material(move(shader), nullptr);
    mat.albedo = albedo;
    return mat;
}

Material Material::Light() {
    auto mat = Material::Base(glm::vec4(1));
    mat.emission = 1.f;
    return mat;
}

void Material::activate(glm::mat4 local) {
    shader_->activate();
    shader_->uniform("skybox_tex", 0);

    shader_->uniform("local", local);
    if (repeat_texture) {
        shader_->uniform("textureMat", local);
    } else {
        shader_->uniform("textureMat", glm::mat4(1));
    }

    if (tex_albedo) {
        tex_albedo->bind(GL_TEXTURE1);
        shader_->uniform("material.has_albedo", true);
        shader_->uniform("material.tex_albedo", 1);
    }

    if (tex_spec) {
        tex_spec->bind(GL_TEXTURE2);
        shader_->uniform("material.has_spec", true);
        shader_->uniform("material.tex_spec", 2);
    }

    if (tex_emission) {
        tex_emission->bind(GL_TEXTURE3);
        shader_->uniform("material.has_emission", true);
        shader_->uniform("material.tex_emission", 3);
    }

    if (tex_sheen) {
        tex_sheen->bind(GL_TEXTURE4);
        shader_->uniform("material.has_sheen", true);
        shader_->uniform("material.tex_sheen", 4);
    }

    shader_->uniform("material.col_albedo", albedo);
    shader_->uniform("material.val_emission", emission);
}

void Material::deactivate() {
    shader_->deactivate();
}
