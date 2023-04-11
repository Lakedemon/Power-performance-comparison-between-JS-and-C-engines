//
// Created by leoni on 26/03/2023.
//

#ifndef OPENGLENGINE_ENGINE_H
#define OPENGLENGINE_ENGINE_H


#include "SceneGraph.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <utility>

class Engine {
private:
    unsigned int timer = 0;
    SceneGraph activeScene;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow *window);

    GLFWwindow* window;
    void renderLoop();
    /*void resizeCanvas();
    void updateTime();*/
public:
    explicit Engine(GLFWwindow* window);
    void start();
    static GLFWwindow* initGLFW(int screenWidth, int screenHeight);
};


#endif //OPENGLENGINE_ENGINE_H
