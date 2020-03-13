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
#include "glmisc/entities/Shape.h"
#include "glmisc/entities/TexturedShape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    auto window = glmisc_setup_window();
    if (window == nullptr) {
        return -1;
    }

    glmisc_debug_setup();

    auto camera = make_unique<Camera>(
            glm::perspective(glm::radians(80.f), 1600.f / 1200.f, 0.1f, 100.f),
            glm::vec3(0, 1, 0),
            glm::vec3(0, 0, -1)
            );

    auto fontTexture = make_shared<Texture2D>(string("../assets/font.png"));
    auto labelText = make_unique<TextObject>(fontTexture, string("$ label test"));

    auto cubeTexture = make_shared<Texture2D>(std::string("../assets/b.png"));

    size_t cubeDataSize;
    auto cubeData = Primitives::Cube(&cubeDataSize);

    size_t planeDataSize;
    auto planeData = Primitives::Plane(&planeDataSize);

    auto cube1 = make_unique<TexturedShape>(cubeTexture, cubeData.get(), cubeDataSize);
    cube1->position = glm::vec3(-1, 1, -2);

    auto cube2 = make_unique<TexturedShape>(cubeTexture, cubeData.get(), cubeDataSize);
    cube2->position = glm::vec3(1, 0.5, -5);

    auto plane = make_unique<Shape>(planeData.get(), planeDataSize);
    plane->scale = glm::vec3(100, 0, 100);
    plane->albedo = glm::vec4(0, 0.3, 0, 1);

    auto lightShape = make_shared<Shape>(cubeData.get(), cubeDataSize);
    lightShape->albedo = glm::vec4(1);
    lightShape->position = glm::vec3(1, 1, -1);
    lightShape->scale = glm::vec3(0.05);
    lightShape->emission = 1;

    auto ambientColor = glm::vec3(0.2, 0.2, 0.2);

    // setup
    glViewport(0, 0, 1600, 1200);

    // stuff
    auto guiProj = glm::mat4(1.f);
    guiProj = glm::scale(guiProj, glm::vec3(2.f / 1600, 2.f / 1200, 1));
    guiProj = glm::translate(guiProj, glm::vec3(-1600 / 2, -1200 / 2, 0));
    labelText->proj = guiProj;

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
        glm::vec3 *pos = &(camera->position);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
            pos = &(lightShape->position);
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            pos->z -= speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            pos->z += speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            pos->x -= speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            pos->x += speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            pos->y += speed * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            pos->y -= speed * deltaTime;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            glEnable(GL_DEPTH_TEST);

            // render plane
            plane->ambientLight = ambientColor;
            plane->prepare_for(camera.get());
            plane->affected_by(lightShape.get());
            plane->render();

            // render cube 1
            cube1->ambientLight = ambientColor;
            cube1->prepare_for(camera.get());
            cube1->affected_by(lightShape.get());
            cube1->render();

            // render cube 2
            cube2->ambientLight = ambientColor;
            cube2->prepare_for(camera.get());
            cube1->affected_by(lightShape.get());
            cube2->render();

             // render light
             lightShape->prepare_for(camera.get());
             lightShape->render();

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
