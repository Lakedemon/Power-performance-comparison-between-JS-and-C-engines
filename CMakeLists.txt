cmake_minimum_required(VERSION 3.22)
project(OpenGLEngine)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
pkg_search_module(GLFW REQUIRED glfw3)
link_libraries(${JSONCPP_LIBRARIES})
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_executable(OpenGLEngine glad.c GL_Helpers/AssetLoader.cpp GL_Helpers/AssetLoader.h  Math/Vector2.cpp Math/glMath.cpp Math/glMath.h GL_Helpers/Shader.cpp GL_Helpers/Shader.h config/config.h Engine/Object3D.cpp Engine/Object3D.h Engine/EmptyObject.cpp Engine/EmptyObject.h Engine/Mesh.cpp Engine/Mesh.h Math/Vector2.h Math/Vector3.h Math/Vector4.h Math/Vector4.cpp Math/Matrix4.cpp Math/Matrix4.h Engine/Transform.cpp Engine/Transform.h Engine/SceneGraph.cpp Engine/SceneGraph.h Engine/SceneGraph.h Engine/Camera.cpp Engine/Camera.h Engine/Camera.h config/config.h Engine/PBRMetallicRoughness.cpp Engine/PBRMetallicRoughness.h Engine/PBRMetallicRoughness.h Math/Vector3.cpp Engine/PointLight.cpp Engine/PointLight.h Engine/Engine.cpp Engine/Engine.h Main.cpp Engine/Animation/Animator.cpp Engine/Animation/Animator.h Engine/Animation/Channel.cpp Engine/Animation/Channel.h Engine/Animation/Sampler.cpp Engine/Animation/Sampler.h)

#[[
add_executable(OpenGLEngine glad.c hello_triangle.cpp)
]]

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS})

#target_link_libraries(${PROJECT_NAME} PUBLIC ${JSONCPP_LIBRARIES} PRIVATE GLEW::GLEW ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${JSONCPP_LIBRARIES} PRIVATE glfw3 GL X11 pthread Xrandr Xi dl)
