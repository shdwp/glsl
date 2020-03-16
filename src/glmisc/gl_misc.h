//
// Created by shdwp on 3/10/2020.
//

#ifndef GLPL_GL_MISC_H
#define GLPL_GL_MISC_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

typedef unsigned int shader_object_t;
typedef unsigned int program_object_t;
typedef unsigned int texture_object_t;
typedef unsigned int vertex_array_object_t;
typedef unsigned int vertex_buffer_object_t;
typedef unsigned int element_array_buffer_object_t;

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

GLFWwindow  *glmisc_setup_window();
void glmisc_debug_setup();

#endif //GLPL_GL_MISC_H
