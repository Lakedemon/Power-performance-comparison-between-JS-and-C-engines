#include "GL_Helpers/AssetLoader.h"
#include "Engine/Engine.h"

int main()
{
    GLFWwindow* window= Engine::initGLFW(Config::screenWidth, Config::screenHeight);
    Engine engine = Engine(window, Config::defaultVS, Config::defaultFS, Config::defaultGLTF, Config::framesToRenderBeforeKill);
    engine.start();
}
