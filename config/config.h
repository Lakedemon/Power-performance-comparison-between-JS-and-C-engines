#ifndef OPENGLENGINE_CONFIG_H
#define OPENGLENGINE_CONFIG_H

#pragma once

#include <string>
#include <filesystem>


namespace Config {
    static const std::string shaderPath("../Shader_sources/");
    static const std::string gltfPath("../Assets/gltf/");
    static const std::string assetPath("../Assets/");

    static const int screenWidth = 1920;
    static const int screenHeight = 1080;
    static const float aspect = 1.77777777778;

    static const unsigned int maxLightsCount = 16;
    static const float clearColor[4]{0.2f, 0.5f, 0.3f, 1.0f};
}

#endif //OPENGLENGINE_CONFIG_H