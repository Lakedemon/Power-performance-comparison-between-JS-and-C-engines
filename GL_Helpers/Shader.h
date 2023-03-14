#ifndef OPENGLENGINE_SHADER_H
#define OPENGLENGINE_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    unsigned int ID;

    Shader(const char* vsPath, const char* fsPath);

public:
    unsigned int getId() const {
        return ID;
    }

private:
    static std::string loadShaderFile(const char * path);
    void initShader(const char* shaderCode, GLenum shaderType) const;
    static void checkCompile(unsigned int shader);
    static void checkLinking(unsigned int program);
};


#endif //OPENGLENGINE_SHADER_H
