#include "Engine.h"

void Engine::renderLoop() {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        activeScene.updateScene();
        activeScene.defaultDraw({});

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::start() {
    this->renderLoop();
}

Engine::Engine(GLFWwindow* window): window(window) {
    Shader mainShader = Shader{"PBR_VS.glsl", "PBR_FS.glsl"};
    this->activeScene = SceneGraph{AssetLoader::loadGLTF("ShapeMuseum.gltf"), mainShader};
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Engine::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window side changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

GLFWwindow *Engine::initGLFW(int screenWidth, int screenHeight) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(1);
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGLEngine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    return window;
}
