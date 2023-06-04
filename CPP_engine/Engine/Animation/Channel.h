#ifndef OPENGLENGINE_CHANNEL_H
#define OPENGLENGINE_CHANNEL_H


#include "../EmptyObject.h"
#include "Sampler.h"
#include <utility>

class Channel {
public:
    Channel(EmptyObject& node, Sampler sampler, std::string path);
    void updateNode(float t);
private:
    EmptyObject& _node;
    Sampler _sampler;
    std::string _path;
};


#endif //OPENGLENGINE_CHANNEL_H
