#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

#include "glmisc/ShaderProgram.h"
#include "glmisc/Texture2D.h"
#include "glmisc/VertexBufferObject.h"
#include "glmisc/Camera.h"
#include "glmisc/text/TextObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    auto window = glmisc_setup_window();
    if (window == nullptr) {
        return -1;
    }

    glmisc_debug_setup();
    glEnable(GL_DEPTH_TEST);
    std::string value = std::string("abc");
    TextObject to(nullptr, &value);

    // setup
    glViewport(0, 0, 1600, 1200);

    double lastFrameTimestamp = glfwGetTime();

    // render loop
    while (!glfwWindowShouldClose(window)) {
        double deltaTime = glfwGetTime() - lastFrameTimestamp;
        lastFrameTimestamp = glfwGetTime();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwTerminate();
            return 0;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 proj = glm::perspective(glm::radians(80.f), 1600.f / 1200.f, 0.1f, 100.f);
        to.render(proj);

        glfwSwapBuffers(window);
        glfwPollEvents();
        double frameTime = glfwGetTime() - lastFrameTimestamp;
        double desiredFrametime = 0.016;
        double desiredSleep = desiredFrametime - frameTime;
    }

    glfwTerminate();
    return 0;
}
