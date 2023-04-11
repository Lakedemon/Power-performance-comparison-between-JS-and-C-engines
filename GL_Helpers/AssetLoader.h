#ifndef OPENGLENGINE_ASSETLOADER_H
#define OPENGLENGINE_ASSETLOADER_H

#include "../config/config.h"
#include "jsoncpp/json/json.h"
#include <iostream>
#include <fstream>

using namespace std;
namespace AssetLoader{
    struct gltf{
        Json::Value j;
        vector<vector<char>> buffers;
    };

    static vector<char> loadBinary(unsigned int byteLength, const string& filePath, const string& assetPath = Config::gltfPath);
    static Json::Value loadJSON(const string& filePath, const string& assetPath = Config::gltfPath);
    gltf loadGLTF(const string& filePath, const string& assetPath = Config::gltfPath);
};


#endif //OPENGLENGINE_ASSETLOADER_H
