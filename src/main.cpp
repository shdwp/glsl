#include <vector>
#include <thread>
#include <iostream>

#include "glmisc/render/ShaderProgram.h"
#include "glmisc/render/Texture2D.h"
#include "glmisc/render/VertexBufferObject.h"
#include "glmisc/scene/Camera.h"
#include "glmisc/text/TextObject.h"
#include "glmisc/objects/GObject.h"
#include "glmisc/objects/Light.h"
#include "glmisc/scene/Scene.h"
#include "glmisc/store/Store.h"
#include "glmisc/render/Framebuffer.h"

int main() {
    auto window = glmisc_setup_window();
    if (window == nullptr) {
        return -1;
    }

    glmisc_debug_setup();

    auto fb = make_unique<Framebuffer>(1600, 1200);

    // cam
    auto camera = make_unique<Camera>(
            glm::perspective(glm::radians(80.f), 1600.f / 1200.f, 0.1f, 100.f),
            glm::vec3(0, 0, 3),
            glm::vec3(0, 0, -1)
    );

    // label
    auto fontTexture = make_shared<Texture2D>("../assets/font.png");

    // scene
    auto scene = make_unique<Scene>();

    auto model = Store::instance().LoadModel("../assets/models", "cube.obj");
    // cube
    auto cube1 = scene->addChild(GObject(model));
    cube1->scale = glm::vec3(1, 1, 1);
    cube1->position = glm::vec3(0, 0, -1);
    cube1->rotation = glm::quat(glm::vec3(glm::radians(0.f), 0, 0));

    // skybox
    auto skybox = make_shared<Skybox>(make_shared<TextureCubemap>((vector<string>) {
        "../assets/skybox/right.jpg",
        "../assets/skybox/left.jpg",
        "../assets/skybox/top.jpg",
        "../assets/skybox/bottom.jpg",
        "../assets/skybox/front.jpg",
        "../assets/skybox/back.jpg",
    }));
    scene->skybox = skybox;

    // plane
    /*
    auto grass_mat = make_shared<Material>(Material::Base(make_shared<Texture2D>("../assets/grass.jpg", GL_LINEAR)));
    grass_mat->repeat_texture = true;

    auto plane = scene->addChild(GObject(Model::Load("../assets/models", "plane.obj", grass_mat)));
    plane->scale = glm::vec3(100, 1, 100);
    plane->position = glm::vec3(0, -1, 0);
     */

    auto direct_light = Light();
    direct_light.type = LightType_Directional;
    direct_light.direction = glm::vec3(0, 1, -1);
    direct_light.specular = glm::vec3(0.5f);
    direct_light.diffuse = glm::vec3(0.8f);
    direct_light.ambient = glm::vec3(0.6f);
    direct_light.setUniformColor(glm::vec3(0.9, 0.9, 1.0));
    scene->addLight(make_shared<Light>(move(direct_light)));

    /*
    auto light_mat = make_shared<Material>(Material::Base(glm::vec4(1)));
    auto point_light = make_shared<Light>();
    point_light->type = LightType_Point;
    point_light->ambient = glm::vec3(0);
    scene->addLight(point_light);

    auto point_light_object = scene->addChild(GObject(Model::Load("../assets/models", "cube.obj", light_mat)));
    point_light_object->scale = glm::vec3(0.1f);
    point_light_object->position = glm::vec3(0, 1, 1);
    point_light_object->addChild(point_light);
     */

    // setup
    glViewport(0, 0, 1600, 1200);

    // stuff
    auto guiProj = glm::mat4(1.f);
    guiProj = glm::scale(guiProj, glm::vec3(2.f / 1600, 2.f / 1200, 1));
    guiProj = glm::translate(guiProj, glm::vec3(-1600 / 2, -1200 / 2, 0));

    auto text = TextObject(fontTexture);

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

        glm::vec3 *pos = &(camera->position);
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) {
            //pos = &(point_light_object->position);
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

        double mousex, mousey;
        glfwGetCursorPos(window, &mousex, &mousey);
        mousey = 1200 - mousey;

        scene->runtime_debug_focus = glm::vec2(mousex, mousey);
        //scene->runtime_debug_flags = RuntimeDebugFlag_FocusPrintf;

        fb->bind();
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        {
            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);
            scene->draw(*camera);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }

        fb->unbind();
        fb->render();

        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // render text
            text.setText(string_format("debug opts: %d", scene->runtime_debug_flags), 24);
            text.render(guiProj);

            glDisable(GL_BLEND);
        }

        if (scene->runtime_debug_flags & RuntimeDebugFlag_FocusPrintf) {
            std::this_thread::sleep_for(std::chrono::milliseconds(128));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
