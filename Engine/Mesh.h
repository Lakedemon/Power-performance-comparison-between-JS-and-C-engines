#ifndef OPENGLENGINE_MESH_H
#define OPENGLENGINE_MESH_H

#include "glad/glad.h"

class Mesh {
public:
    Mesh(float* position, float* normal, float* texcoord_0, unsigned int* index);
    unsigned int getVao() const;
private:
    float *_position, *_normal, *_texcoord_0;
    unsigned int* _index, VAO;
    void createBufferedState();
    static void bufferFloats(float &floats, unsigned int location);
    static void bufferIndex(unsigned int &ints);
};
#endif //OPENGLENGINE_MESH_H