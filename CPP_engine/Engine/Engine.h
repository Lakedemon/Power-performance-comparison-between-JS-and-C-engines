#ifndef OPENGLENGINE_ENGINE_H
#define OPENGLENGINE_ENGINE_H

#include "../GL_Helpers/AssetLoader.h"
#include "SceneGraph.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <utility>
#include <chrono>


class Engine {
private:
    int framesElapsed = 0;
    int runForNFrames = 0;

    std::chrono::steady_clock::time_point startTime;
    float timer = 0;
    SceneGraph activeScene;

    static void resizeWindow(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow *window);

    GLFWwindow* window;
    void renderLoop();
    void updateTime();
public:
    Engine(GLFWwindow* window, const std::string& vsName, const std::string& fsName, const std::string& gltfName, int runForNFrames);
    void start();
    static GLFWwindow* initGLFW(int screenWidth, int screenHeight);
};


#endif //OPENGLENGINE_ENGINE_H
