cmake_minimum_required(VERSION 3.15)
project(glpl)

set(CMAKE_CXX_STANDARD 17)

# glad
add_library(glad.lib src/glad/glad.c)
target_include_directories(glad.lib PRIVATE include)

# stb_image
add_library(stb_image.lib src/stb_image/stb_image.cpp)
target_include_directories(stb_image.lib PRIVATE include)

# tinyobjloader
add_library(tiny_obj_loader.lib src/tiny_obj_loader/tiny_obj_loader.cc)
target_include_directories(tiny_obj_loader.lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# fmt
add_library(fmt.lib src/fmt/format.cc src/fmt/posix.cc)
target_include_directories(fmt.lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# main app
set(SOURCE_FILES
        src/main.cpp
        src/glmisc/gl_misc.h
        src/glmisc/gl_misc.cpp
        src/glmisc/render/ShaderProgram.cpp
        src/glmisc/render/ShaderProgram.h
        src/glmisc/render/Texture2D.cpp
        src/glmisc/render/Texture2D.h
        src/glmisc/render/VertexBufferObject.cpp
        src/glmisc/render/VertexBufferObject.h
        src/glmisc/scene/Camera.cpp
        src/glmisc/scene/Camera.h
        src/glmisc/text/TextObject.cpp
        src/glmisc/text/TextObject.h
        src/glmisc/objects/GObject.cpp
        src/glmisc/objects/GObject.h
        src/glmisc/render/Material.cpp
        src/glmisc/render/Material.h
        src/glmisc/objects/Light.cpp
        src/glmisc/objects/Light.h
        src/glmisc/scene/Scene.cpp
        src/glmisc/scene/Scene.h
        src/glmisc/render/UniformBufferObject.cpp
        src/glmisc/render/UniformBufferObject.h
        src/glmisc/util/util.h
        src/glmisc/render/Model.cpp
        src/glmisc/render/Model.h
        src/glmisc/store/Store.cpp
        src/glmisc/store/Store.h
        src/glmisc/util/runtime_debug.h
        src/glmisc/render/Framebuffer.cpp
        src/glmisc/render/Framebuffer.h
        src/glmisc/render/TextureCubemap.cpp
        src/glmisc/render/TextureCubemap.h
        src/glmisc/objects/Skybox.cpp
        src/glmisc/objects/Skybox.h)

add_executable(glpl ${SOURCE_FILES})
set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-include ../src/pch.h")
target_include_directories(glpl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# link libs
target_link_libraries(glpl ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a)
target_link_libraries(glpl glad.lib)
target_link_libraries(glpl stb_image.lib)
target_link_libraries(glpl opengl32.lib)
target_link_libraries(glpl tiny_obj_loader.lib)
target_link_libraries(glpl fmt.lib)
