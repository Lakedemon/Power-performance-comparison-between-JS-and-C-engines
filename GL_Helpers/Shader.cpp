#include "Shader.h"

Shader::Shader(const char* vsPath, const char* fsPath){
    std::string vSource = loadShaderFile(vsPath);
    std::string fSource = loadShaderFile(fsPath);

    const char * vs = vSource.c_str();
    const char * fs = fSource.c_str();

    ID = glCreateProgram();
    initShader(vs, GL_VERTEX_SHADER);
    initShader(fs, GL_FRAGMENT_SHADER);

    glLinkProgram(ID);
    checkLinking(ID);
}

std::string Shader::loadShaderFile(const char * path){
    std::ifstream file;
    std::string contents;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << file.rdbuf();
        file.close();
        contents = vShaderStream.str();
    }
    catch(std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    return contents;
}

void Shader::initShader(const char* shaderCode, GLenum shaderType) const{
    unsigned int shader;
    shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);
    checkCompile(shader);

    glAttachShader(ID, shader);
    glDeleteShader(shader);
}

void Shader::checkCompile(unsigned int shader) {
    int status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){
        unsigned short logSize = 1024;
        char log[logSize];
        glGetShaderInfoLog(shader, logSize, nullptr, log);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: SHADER" << "\n" << log << std::endl;
    }
}

void Shader::checkLinking(unsigned int program) {
    int status;

    glGetProgramiv(program, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){
        unsigned short logSize = 1024;
        char log[logSize];
        glGetProgramInfoLog(program, logSize, nullptr, log);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM" << "\n" << log << std::endl;
    }
}