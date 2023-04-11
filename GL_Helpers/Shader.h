#ifndef OPENGLENGINE_SHADER_H
#define OPENGLENGINE_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../config/config.h"

class Shader {
public:
    Shader(const std::string& vsPath, const std::string& fsPath);
    Shader();
    [[nodiscard]] unsigned int getId() const;
private:
    unsigned int ID{};
    static std::string loadShaderFile(const std::string& path);
    void initShader(const char* shaderCode, GLenum shaderType) const;
    static void checkCompile(unsigned int shader);
    static void checkLinking(unsigned int program);
};


#endif //OPENGLENGINE_SHADER_H
