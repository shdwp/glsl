#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

#include "glmisc/gl/ShaderProgram.h"
#include "glmisc/gl/Texture2D.h"
#include "glmisc/gl/VertexBufferObject.h"
#include "glmisc/scene/Camera.h"
#include "glmisc/text/TextObject.h"
#include "glmisc/gen/Primitives.h"
#include "glmisc/objects/GObject.h"
#include "glmisc/objects/Light.h"
#include "glmisc/scene/Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    auto window = glmisc_setup_window();
    if (window == nullptr) {
        return -1;
    }

    glmisc_debug_setup();

    // cam
    auto camera = make_unique<Camera>(
            glm::perspective(glm::radians(80.f), 1600.f / 1200.f, 0.1f, 100.f),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, -1)
    );

    // label
    auto fontTexture = make_shared<Texture2D>("../assets/font.png");
    auto labelText = make_unique<TextObject>(fontTexture, "$ label test");

    // scene
    auto scene = make_unique<Scene>();

    // cubes
    size_t cubeDataSize;
    auto cubeData = Primitives::Cube(&cubeDataSize);
    auto cubeMat = make_shared<Material>(Material::Base(make_shared<Texture2D>("../assets/a_diff.png")));
    cubeMat->tex_spec_ = make_shared<Texture2D>("../assets/a_spec.png");
    cubeMat->tex_emission_ = make_shared<Texture2D>("../assets/a_emission.png");

    auto cube1 = scene->addChild(GObject(cubeMat, cubeData.get(), cubeDataSize));
    cube1->position_ = glm::vec3(-0.5, 0.5, -3);
    auto cube2 = scene->addChild(GObject(cubeMat, cubeData.get(), cubeDataSize));
    cube2->position_ = glm::vec3(1, 0.5, -5);
    auto cube3 = scene->addChild(GObject(cubeMat, cubeData.get(), cubeDataSize));
    cube3->position_ = glm::vec3(-2, 0.5, -5);

    // plane
    size_t planeDataSize;
    auto planeData = Primitives::Plane(&planeDataSize);
    auto plane = scene->addChild(GObject(
            make_shared<Material>(Material::Base(make_shared<Texture2D>("../assets/grass.jpg", GL_LINEAR))),
            planeData.get(),
            planeDataSize
    ));
    plane->scale_ = glm::vec3(100, 1, 100);

    // light
    auto light = scene->addChild(Spotlight(make_shared<Material>(Material::Light()), cubeData.get(), cubeDataSize));
    light->position_ = glm::vec3(1, 1, -1);
    light->scale_ = glm::vec3(0.05);
    light->ambient_ = glm::vec3(0.15f);
    scene->direction_light_ = light;

    // setup
    glViewport(0, 0, 1600, 1200);

    // stuff
    auto guiProj = glm::mat4(1.f);
    guiProj = glm::scale(guiProj, glm::vec3(2.f / 1600, 2.f / 1200, 1));
    guiProj = glm::translate(guiProj, glm::vec3(-1600 / 2, -1200 / 2, 0));
    labelText->proj_ = guiProj;

    // render loop
    double lastFrameTimestamp = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double deltaTime = glfwGetTime() - lastFrameTimestamp;
        lastFrameTimestamp = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwTerminate();
            return 0;
        }

        auto speed = 1.f;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
            speed *= 4.f;
        }

        glm::vec3 *pos = &(camera->position_);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
            pos = &(light->position_);
        }

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            pos->y -= speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            pos->y += speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            pos->x -= speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            pos->x += speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            pos->z += speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            pos->z -= speed * deltaTime;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            glEnable(GL_DEPTH_TEST);
            scene->draw(*camera);
            glDisable(GL_DEPTH_TEST);
        }

        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // render text
            labelText->render();
            glDisable(GL_BLEND);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
