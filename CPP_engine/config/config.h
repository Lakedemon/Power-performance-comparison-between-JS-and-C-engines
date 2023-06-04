#ifndef OPENGLENGINE_CONFIG_H
#define OPENGLENGINE_CONFIG_H

#pragma once

#include <string>
#include <filesystem>


namespace Config {
    static const std::string shaderPath("../Shader_sources/");
    static const std::string gltfPath("../Assets/gltf/");
    static const std::string assetPath("../Assets/");

    static const std::string defaultVS("PBR_VS.glsl");
    static const std::string defaultFS("PBR_FS.glsl");

    static const int screenWidth = 1920;
    static const int screenHeight = 1080;
    static const float aspect = 1.77777777778;
    static const unsigned int maxLightsCount = 16;
    static const int glfwSwapInterval = 0; //0 to disable vsync

    static const float clearColor[4]{0.2f, 0.5f, 0.3f, 1.0f};

    //Change me as you want
    static const std::string defaultGLTF("Scenario2.gltf");
    static const int framesToRenderBeforeKill = 1440;
}

#endif //OPENGLENGINE_CONFIG_H