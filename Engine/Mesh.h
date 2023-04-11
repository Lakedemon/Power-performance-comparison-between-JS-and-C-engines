#ifndef OPENGLENGINE_MESH_H
#define OPENGLENGINE_MESH_H

#include <glad/glad.h>
#include "../Math/Vector3.h"

class Mesh {
public:
    Mesh(float* position, float* normal, float* texcoord_0, unsigned int* index);
    Mesh() = default;
    [[nodiscard]] unsigned int getVao() const;
    int drawCount();
    //Vector3 boundingBox();
    float boundingRadius();
private:
    float *_position, *_normal, *_texcoord_0;
    unsigned int* _index;
    unsigned int VAO = 0;

    void createBufferedState();
    static void bufferFloats(float &floats, unsigned int location);
    static void bufferIndex(unsigned int &ints);
};
#endif //OPENGLENGINE_MESH_H