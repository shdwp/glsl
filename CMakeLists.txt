cmake_minimum_required(VERSION 3.15)
project(glpl)

set(CMAKE_CXX_STANDARD 14)

add_library(glad.lib src/glad/glad.c)
add_library(stb_image.lib src/stb_image/stb_image.cpp)

set(SOURCE_FILES
        src/main.cpp
        src/glmisc/gl_misc.h
        src/glmisc/gl_misc.cpp
        src/glmisc/gl/ShaderProgram.cpp
        src/glmisc/gl/ShaderProgram.h
        src/glmisc/gl/Texture2D.cpp
        src/glmisc/gl/Texture2D.h
        src/glmisc/gl/VertexBufferObject.cpp
        src/glmisc/gl/VertexBufferObject.h
        src/glmisc/scene/Camera.cpp
        src/glmisc/scene/Camera.h
        src/glmisc/text/TextObject.cpp
        src/glmisc/text/TextObject.h
        src/glmisc/gen/Primitives.cpp
        src/glmisc/gen/Primitives.h
        src/glmisc/entities/Shape.cpp
        src/glmisc/entities/Shape.h
        src/glmisc/entities/TexturedShape.cpp src/glmisc/entities/TexturedShape.h)

add_executable(glpl ${SOURCE_FILES})
set_source_files_properties(${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-include ../src/pch.h")

target_include_directories(glad.lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(stb_image.lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(glpl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(glpl ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a)
target_link_libraries(glpl glad.lib)
target_link_libraries(glpl stb_image.lib)
target_link_libraries(glpl opengl32.lib)

