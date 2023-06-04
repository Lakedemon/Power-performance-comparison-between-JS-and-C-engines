#include "AssetLoader.h"

vector<char> AssetLoader::loadBinary(unsigned int byteLength, const string& filePath, const string& assetPath) {
    ifstream binFile = ifstream(assetPath + filePath);

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