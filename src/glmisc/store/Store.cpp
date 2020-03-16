//
// Created by shdwp on 3/16/2020.
//

#include <tiny_obj_loader/tiny_obj_loader.h>
#include <fstream>
#include "Store.h"
#include "windows.h"

Store& Store::instance() {
    static Store _instance;
    return _instance;
}

shared_ptr<Model> Store::LoadModel(string base_path, string name) {
    tinyobj::attrib_t attrib;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> materials;

    string warn, err;
    auto ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, (base_path + "/" + name).c_str(), base_path.c_str());
    assert(ret);

    vector<VertexBufferObject> result_buffers;
    vector<shared_ptr<Material>> result_materials;

    for (size_t i = 0; i < shapes.size(); i++) {
        auto mesh = &(shapes[i].mesh);

        vector<float> vertices;
        vector<float> normals;
        vector<float> texture_coords;
        vector<uint32_t> indices;

        size_t index_offset = 0;
        for (size_t f = 0; f < mesh->num_face_vertices.size(); f++) {
            for (size_t v = 0; v < mesh->num_face_vertices[f]; v++) {
                auto idx = mesh->indices[index_offset + v];

                indices.push_back(vertices.size() / 3);
                vertices.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
                vertices.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
                vertices.push_back(attrib.vertices[3 * idx.vertex_index + 2]);

                normals.push_back(attrib.normals[3 * idx.normal_index + 0]);
                normals.push_back(attrib.normals[3 * idx.normal_index + 1]);
                normals.push_back(attrib.normals[3 * idx.normal_index + 2]);

                if (!attrib.texcoords.empty()) {
                    texture_coords.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
                    texture_coords.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
                }
            }

            index_offset += mesh->num_face_vertices[f];
        }

        auto mesh_mat = materials[mesh->material_ids[0]];
        auto mat = make_shared<Material>(Material::Base(glm::vec4(0)));

        if (!mesh_mat.diffuse_texname.empty()) {
            mat->tex_albedo = make_shared<Texture2D>(base_path + "/" + mesh_mat.diffuse_texname);
        } else {
            mat->albedo = glm::vec4(mesh_mat.diffuse[0], mesh_mat.diffuse[1], mesh_mat.diffuse[2], 1);
        }

        if (!mesh_mat.specular_texname.empty()) {
            mat->tex_spec = make_shared<Texture2D>(base_path + "/" + mesh_mat.specular_texname);
        }

        if (!mesh_mat.emissive_texname.empty()) {
            mat->tex_emission = make_shared<Texture2D>(base_path + "/" + mesh_mat.emissive_texname);
        }

        if (!mesh_mat.sheen_texname.empty()) {
            mat->tex_sheen = make_shared<Texture2D>(base_path + "/" + mesh_mat.sheen_texname);
        }

        result_materials.emplace_back(mat);
        result_buffers.emplace_back(VertexBufferObject(vertices, texture_coords, normals, indices));
    }

    return make_shared<Model>(Model(result_buffers, result_materials));
}
