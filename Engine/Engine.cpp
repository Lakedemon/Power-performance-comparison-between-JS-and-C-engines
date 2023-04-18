#include "Engine.h"

void Engine::renderLoop() {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        this->updateTime();
        activeScene.animate(timer / 1000);
        activeScene.updateScene();
        activeScene.portalDraw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::start() {
    this->renderLoop();
}

Engine::Engine(GLFWwindow* window, const std::string& vsName, const std::string& fsName, const std::string& gltfName): window(window) {
    startTime = std::chrono::steady_clock::now();
    Shader mainShader = Shader{vsName, fsName};
    this->activeScene = SceneGraph{AssetLoader::loadJSON(gltfName), mainShader};
}

void Engine::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Engine::resizeWindow(GLFWwindow *window, int width, int height) {
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
        std::cout << "ERROR::GLAD::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::GLAD::FAILED_TO_INITIALIZE" << std::endl;
    }

    return window;
}

void Engine::updateTime() {
    timer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
}
