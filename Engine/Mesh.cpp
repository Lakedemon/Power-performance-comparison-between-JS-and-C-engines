#include "Mesh.h"

Mesh::Mesh(std::vector<float> position, std::vector<float> normal, std::vector<float> texcoord_0, std::vector<uint16_t> index) : _position(std::move(position)), _normal(std::move(normal)), _texcoord_0(std::move(texcoord_0)), _index(std::move(index)) {
    createBufferedState();
}

int Mesh::drawCount() const {
    return _index.size();
}

std::vector<Vector3>& Mesh::boundingBox(std::vector<Vector3>& target) {
    int size = (int)this->_position.size() / 3;
    float one[size], two[size], three[size];

    for (int j = 0, i = 0; i < this->_position.size(); i+=3) {
        one[j] = this->_position.at(i);
        two[j] = this->_position.at(i + 1);
        three[j] = this->_position.at(i + 2);
        j++;
    }

    auto [minX, maxX] = std::minmax_element(one, one + this->_position.size() * sizeof(float));
    auto [minY, maxY] = std::minmax_element(one, one + this->_position.size() * sizeof(float));
    auto [minZ, maxZ] = std::minmax_element(one, one + this->_position.size() * sizeof(float));

    target.emplace_back(*minX, *minY, *minZ);
    target.emplace_back(*minX, *minY, *maxZ);
    target.emplace_back(*minX, *maxY, *minZ);
    target.emplace_back(*minX, *maxY, *maxZ);
    target.emplace_back(*maxX, *minY, *minZ);
    target.emplace_back(*maxX, *minY, *maxX);
    target.emplace_back(*maxX, *maxY, *minZ);
    target.emplace_back(*maxX, *maxY, *maxZ);

    return target;
}

float Mesh::boundingRadius(Vector3 axisFilter = Vector3::one) {
    std::vector<Vector3> bb;
    boundingBox(bb);
    std::for_each(bb.begin(), bb.end(), [&](Vector3 v){v *= axisFilter;});
    float dis[3] {
        Vector3::distance(bb.at(0), bb.at(1)),
        Vector3::distance(bb.at(0), bb.at(2)),
        Vector3::distance(bb.at(0), bb.at(4)),
    };
    return *std::max_element(dis, dis + 3 * sizeof (Vector3));
}

void Mesh::createBufferedState() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    bufferFloats(_position, 0, 3);
    bufferFloats(_normal, 1, 3);
    bufferFloats(_texcoord_0, 2, 2);
    bufferIndex(_index);
}

void Mesh::bufferFloats(std::vector<float> floats, unsigned int location, int size) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, floats.size() * sizeof (float), &floats.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::bufferIndex(std::vector<uint16_t> ints) {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ints.size() * sizeof (uint16_t), &ints.front(), GL_STATIC_DRAW);
}

unsigned int Mesh::getVao() const {
    return VAO;
}


