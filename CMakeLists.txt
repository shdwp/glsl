cmake_minimum_required(VERSION 3.15)
project(glpl)

set(CMAKE_CXX_STANDARD 14)

add_library(glad.lib src/glad/glad.c)
add_library(stb_image.lib src/stb_image/stb_image.cpp)

add_executable(glpl src/main.cpp src/glmisc/gl_misc.h src/glmisc/gl_misc.cpp src/glmisc/ShaderProgram.cpp src/glmisc/ShaderProgram.h src/glmisc/Texture2D.cpp src/glmisc/Texture2D.h src/glmisc/VertexBufferObject.cpp src/glmisc/VertexBufferObject.h src/glmisc/Camera.cpp src/glmisc/Camera.h src/glmisc/text/TextObject.cpp src/glmisc/text/TextObject.h)

target_include_directories(glad.lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(stb_image.lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(glpl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(glpl ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a)
target_link_libraries(glpl glad.lib)
target_link_libraries(glpl stb_image.lib)
target_link_libraries(glpl opengl32.lib)

