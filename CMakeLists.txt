cmake_minimum_required(VERSION 3.22)
project(OpenGLEngine)

find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(CMAKE_CXX_STANDARD 23)

add_executable(OpenGLEngine hello_triangle.cpp glad.c Math/Vector2.cpp Math/glMath.cpp Math/glMath.h GL_Helpers/Shader.cpp GL_Helpers/Shader.h config/config.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW ${GLFW_LIBRARIES})