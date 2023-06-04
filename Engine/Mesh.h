#ifndef OPENGLENGINE_MESH_H
#define OPENGLENGINE_MESH_H

#include <glad/glad.h>
#include "../Math/Vector3.h"
#include <vector>
#include <iostream>
#include <tuple>

class Mesh {
public:
    Mesh(std::vector<float> position, std::vector<float> normal, std::vector<float> texcoord_0, std::vector<uint16_t> index);
    Mesh() = default;
    [[nodiscard]] unsigned int getVao() const;
    [[nodiscard]] int drawCount() const;
    std::vector<Vector3>& boundingBox(std::vector<Vector3>& target);
    float boundingRadius(Vector3 axisFilter);
private:
    std::vector<float> _position, _normal, _texcoord_0;
    std::vector<uint16_t> _index;
    unsigned int VAO = 0;

    void createBufferedState();
    static void bufferFloats(std::vector<float> floats, unsigned int location, int size);
    static void bufferIndex(std::vector<uint16_t> ints);
};
#endif //OPENGLENGINE_MESH_H