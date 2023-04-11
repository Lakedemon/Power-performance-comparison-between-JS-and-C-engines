#include "AssetLoader.h"

AssetLoader::gltf AssetLoader::loadGLTF(const string& filePath, const string& assetPath) {
    Json::Value j = loadJSON(filePath, assetPath);

    vector<vector<char>> buffers;
    for (auto& buffer : j["buffers"]) {
        buffers.push_back(loadBinary(buffer["byteLength"].asInt(), buffer["uri"].asString(), assetPath));
    }

    return {j, buffers};
}

vector<char> AssetLoader::loadBinary(unsigned int byteLength, const string& filePath, const string& assetPath) {
    ifstream binFile = ifstream(assetPath + filePath, ios::binary | ios::ate);

    binFile.seekg(0);
    vector<char> bin(byteLength);
    binFile.read(bin.data(), byteLength);
    binFile.close();

    return bin;
}

Json::Value AssetLoader::loadJSON(const string& filePath, const string& assetPath) {
    ifstream jsonFile(assetPath + filePath);

    Json::Value json;
    try{
        jsonFile >> json;
    }catch(const exception& e){
        cout << "Failed to parse JSON file: " << e.what() << endl;
    }
    jsonFile.close();

    return json;
}