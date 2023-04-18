#include "GL_Helpers/AssetLoader.h"
#include "Engine/Engine.h"

int main()
{
    GLFWwindow* window= Engine::initGLFW(Config::screenWidth, Config::screenHeight);
    Engine engine = Engine(window, "PBR_VS.glsl", "PBR_FS.glsl", "ShapeMuseum.gltf");
    engine.start();
}
