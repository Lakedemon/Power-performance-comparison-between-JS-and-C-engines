#include "Mesh.h"

Mesh::Mesh(float* position, float* normal, float* texcoord, unsigned int* index) {
    this->_position = position;
    this->_normal = normal;
    this->_texcoord_0 = texcoord;
    this->_index = index;
    createBufferedState();
}

void Mesh::createBufferedState() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    bufferFloats(*_position, 0);
    bufferFloats(*_normal, 1);
    bufferFloats(*_texcoord_0, 2);
    bufferIndex(*_index);
}

void Mesh::bufferFloats(float &floats, unsigned int location) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (floats), &floats, GL_STATIC_DRAW);
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::bufferIndex(unsigned int &ints) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (ints), &ints, GL_STATIC_DRAW);
}

unsigned int Mesh::getVao() const {
    return VAO;
}


