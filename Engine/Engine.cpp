#include "Engine.h"

void Engine::renderLoop() {
    while (!(glfwWindowShouldClose(window) || framesElapsed >= runForNFrames && runForNFrames >= 0)) {
        processInput(window);

        this->updateTime();
        activeScene.animate(timer / 1000);
        activeScene.updateScene();
        activeScene.portalDraw();

        glfwSwapBuffers(window);
        glfwPollEvents();

        framesElapsed++;
        std::cout << framesElapsed << std::endl;
    }

    glfwTerminate();
}

void Engine::start() {
    this->renderLoop();
}

Engine::Engine(GLFWwindow* window, const std::string& vsName, const std::string& fsName, const std::string& gltfName, int runForNFrames = 0): window(window), runForNFrames(runForNFrames) {
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
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "OpenGLEngine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "ERROR::GLAD::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(Config::glfwSwapInterval);
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
