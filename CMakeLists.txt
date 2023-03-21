cmake_minimum_required(VERSION 3.22)
project(OpenGLEngine)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
link_libraries(${JSONCPP_LIBRARIES})
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(OpenGLEngine hello_triangle.cpp glad.c Math/Vector2.cpp Math/glMath.cpp Math/glMath.h GL_Helpers/Shader.cpp GL_Helpers/Shader.h config/config.h Engine/Object3D.cpp Engine/Object3D.h Engine/EmptyObject.cpp Engine/EmptyObject.h Engine/Mesh.cpp Engine/Mesh.h Math/Vector2.h Math/Vector3.h Math/Vector4.h Math/Vector4.cpp Math/Matrix4.cpp Math/Matrix4.h Engine/Transform.cpp Engine/Transform.h Engine/SceneGraph.cpp Engine/SceneGraph.h Engine/SceneGraph.h Engine/Camera.cpp Engine/Camera.h Engine/Camera.h GL_Helpers/AssetLoader.cpp GL_Helpers/AssetLoader.h GL_Helpers/AssetLoader.h config/config.h Engine/PBRMetallicRoughness.cpp Engine/PBRMetallicRoughness.h Engine/PBRMetallicRoughness.h Math/Vector3.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW ${GLFW_LIBRARIES})